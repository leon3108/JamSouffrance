#include "server.hpp"

void Server::do_receive()
{
    {
        socket_.async_receive_from(
            boost::asio::buffer(data_, 1024), sender_endpoint_,
            [this](boost::system::error_code ec, std::size_t length)
            {
                std::thread([this, length, ec]()
                            {
                    if (std::find(clients.begin(), clients.end(), sender_endpoint_) == clients.end())
                    {
                        clients.push_back(sender_endpoint_);
                        std::cout << "New client connected: " << sender_endpoint_ << std::endl;
                        Connection data;
                        std::memcpy(&data, data_, sizeof(Connection));
                        data.uuid = boost::uuids::random_generator()();
                        std::memcpy(data_, &data, sizeof(Connection));
                        socket_.send_to(boost::asio::buffer(data_, length), sender_endpoint_);
                    }
                    else if (!ec && length > 0)
                    {
                        Data data;
                        std::memcpy(&data, data_, sizeof(Data));
                        for (std::size_t i = 0; i != clients.size(); i++)
                        {
                            if (clients[i] == sender_endpoint_)
                            {
                                std::cout << "Received DATA from client[" << i << "]: data.x = " << data.playerPosX << ", data.y = " << data.playerPosY << ", data.uuid = " << data.uuid << std::endl;
                                break;
                            }
                        }
                        do_send(length);
                    } })
                    .join();
                do_receive();
            });
    }
}

void Server::do_send(std::size_t length)
{
    std::thread([this, length]()
                {
                    for (std::size_t i = 0; i != clients.size(); i++)
                    {
                        Data data;
                        std::memcpy(&data, data_, sizeof(Data));
                        socket_.send_to(boost::asio::buffer(data_, length), clients[i]);
                        std::cout << "SEND data from server to client[" << i << "]: "
                                  << "uuid: " << data.uuid << std ::endl;
                    } })
        .join();
}

int main()
{
    try
    {
        io_context io_context;
        Server server(io_context);
        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}