#include "./client.hpp"

UdpClient::UdpClient()
    : io_context_(),
      socket_(io_context_, udp::endpoint(udp::v4(), 0)),
      endpoint_(boost::asio::ip::address::from_string("10.109.226.42"), 7979)
{
  data_ = std::make_shared<std::vector<Data>>();
}

boost::uuids::uuid UdpClient::connect()
{
  Connection data;
  char buf[sizeof(Connection)];
  std::memcpy(buf, &data, sizeof(Connection));
  socket_.send_to(boost::asio::buffer(buf, sizeof(Connection)), endpoint_);
  socket_.receive_from(boost::asio::buffer(recv_buf_, sizeof(Connection)), endpoint_);
  std::memcpy(&data, recv_buf_, sizeof(Connection));
  return data.uuid;
}

UdpClient::~UdpClient()
{
  socket_.close();
}

void UdpClient::send(const Data &data)
{
  char buf[sizeof(Data)];
  std::memcpy(buf, &data, sizeof(Data));
  socket_.send_to(boost::asio::buffer(buf, sizeof(Data)), endpoint_);
  // std::cout << "Send Data To Server: x: " << data.playerPosX << ", y: " << data.playerPosY << ", id: " << data.id << ", uuid: " << data.uuid << std::endl;
}

void UdpClient::receive()
{
  socket_.async_receive_from(
      boost::asio::buffer(recv_buf_, sizeof(Data)),
      endpoint_,
      [this](boost::system::error_code ec, std::size_t bytes_recvd)
      {
        // std::cout << bytes_recvd << std::endl;
        if (!ec && bytes_recvd > 0)
        {
          Data data;
          std::memcpy(&data, recv_buf_, sizeof(Data));
          data_->push_back(data);
          /*for (const auto &d : *data_)
          {
            std::cout << "iciiiiii" << d.playerPosX << ", " << d.playerPosY << ", " << d.id << ", " << d.uuid << std::endl;
          }*/
          // std::cout << "Received: " << data.playerPosX << " " << data.playerPosY << " " << data.id << " " << data.uuid << std::endl;
        }
        else
        {
          std::cerr << "Error: " << ec.message() << std::endl;
        }
        receive();
      });
}

std::vector<Data> UdpClient::getData()
{
  // if (data_->empty())
  //   std::cout << "vide\n";
  // for (const auto &d : *data_)
  // {
  //   std::cout << d.playerPosX << ", " << d.playerPosY << ", " << d.id << ", " << d.uuid << std::endl;
  // }
  return *data_;
}

void UdpClient::clearData()
{
  data_->clear();
}

void UdpClient::poll()
{
  io_context_.poll();
}
