#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include "connection.h"
#include <boost/serialization/vector.hpp>

#include "transaction.h"

class Client {
public:
	Client(boost::asio::io_service&, const std::string&, const std::string&);
	void handleConnect(const boost::system::error_code&, boost::asio::ip::tcp::resolver::iterator);
	void handleWrite(const boost::system::error_code&);
	void setTransaction(Transaction);
private:
	Connection connection;
	Transaction transaction;
};