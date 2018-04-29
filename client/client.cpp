#include "client.h"

Client::Client(boost::asio::io_service& io_service, const std::string& host, const std::string& service)
	: connection(io_service) {
	boost::asio::ip::tcp::resolver resolver(io_service);
	boost::asio::ip::tcp::resolver::query query(host, service);
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
	connection.socket().async_connect(endpoint, boost::bind(&client::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator));
}

void Client::handleConnect(const boost::system::error_code& e,boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	if (!e) {
		connection.asyncWrite(transaction, boost::bind(&client::handle_read, this, boost::asio::placeholders::error));
	}
	else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) {
		connection.socket().close();
		boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
		connection.socket().async_connect(endpoint, boost::bind(&client::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator));
	}
	else {
		std::cerr << e.message() << std::endl;
	}
}

void Client::handleWrite(const boost::system::error_code& e) {
	if (!e) {
		;//give message to user of wallet?
	}
	else {
		std::cerr << e.message() << std::endl;
	}
}