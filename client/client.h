#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include "Connection.h"
#include <boost/serialization/vector.hpp>

#include "transaction.h"

class Client {
public:
	Client(boost::asio::io_service&, const std::string&, const std::string&);
	void handleConnect(const boost::system::error_code&, boost::asio::ip::tcp::resolver::iterator);
	void handleWrite(const boost::system::error_code&);
private:
	Connection connection;
	std::vector<Transaction> transaction;	//not sure why it is a vector, ping me when implementing
};