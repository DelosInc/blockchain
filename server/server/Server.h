#pragma once
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include "Connection.h"
#include <boost/serialization/vector.hpp>

class Server
{
public:
	Server(boost::asio::io_context&, unsigned short);
	void handleAccept(const boost::system::error_code&, connection_ptr);
	void handleRead(const boost::system::error_code&, connection_ptr);
private:
	boost::asio::ip::tcp::acceptor acceptor;
	Transaction transaction;
};

