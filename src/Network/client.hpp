#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <chrono>
#include <thread>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using boost::asio::ip::udp;
// int PORT = 8080;

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

class UdpClient
{
public:
    UdpClient();
    ~UdpClient();
    void send(const Data &data);
    void receive();
    std::vector<Data> getData();
    void poll();
    void clearData();
    boost::uuids::uuid connect();

private:
    boost::asio::io_context io_context_;
    udp::socket socket_;
    udp::endpoint endpoint_;
    char recv_buf_[sizeof(Data)];
    std::shared_ptr<std::vector<Data>> data_;
    boost::uuids::uuid uuid;
};
