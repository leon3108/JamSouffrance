#ifndef _SERVER_
#define _SERVER_

#include <iostream>
#include <thread>
#include <memory>
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;
using boost::asio::ip::udp;

struct Data
{
    int id;
    int playerPosX;
    int playerPosY;
    boost::uuids::uuid uuid;
};

struct Connection
{
    boost::uuids::uuid uuid;
};

const int PORT = 7979;

class Server
{
public:
    Server(io_context &io_context) : socket_(io_context, udp::endpoint(ip::address::from_string("10.109.226.42"), PORT))
    {
        do_receive();
    }

private:
    void do_receive();
    void do_send(std::size_t length);

    udp::socket socket_;
    udp::endpoint sender_endpoint_;
    std::vector<udp::endpoint> clients;
    char data_[1024];
};

#endif