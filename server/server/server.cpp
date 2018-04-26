#include "Server.h"

Server::Server(boost::asio::io_context& io_context, unsigned short port)
	: acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
	connection_ptr new_conn(new Connection(acceptor.get_io_context()));
	acceptor.async_accept(new_conn->getSocket(), boost::bind(&Server::handleAccept, this, boost::asio::placeholders::error, new_conn));
}

void Server::handleAccept(const boost::system::error_code& e, connection_ptr conn) {
	if (!e) {
		conn->asyncRead(transaction, boost::bind(&Server::handleRead, this, boost::asio::placeholders::error));
	}
	connection_ptr new_conn(new Connection(acceptor.get_io_context()));
	acceptor.async_accept(new_conn->getSocket(), boost::bind(&Server::handleAccept, this, boost::asio::placeholders::error, new_conn));
}

void Server::handleRead(const boost::system::error_code& e, connection_ptr conn) {
	//push to queue
}

