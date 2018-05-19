#include "Server.h"

Server::Server(boost::asio::io_context& io_context, unsigned short port, QueueHandler *currentQueue)
	: acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
	currentQueue(currentQueue) {
	boost::shared_ptr<Connection> new_conn(new Connection(acceptor.get_io_context()));
	acceptor.async_accept(new_conn->getSocket(), boost::bind(&Server::handleAccept, this, boost::asio::placeholders::error, new_conn));
}

void Server::handleAccept(const boost::system::error_code& e, boost::shared_ptr<Connection> conn) {
	if (!e) {
		conn->asyncRead(transaction, boost::bind(&QueueHandler::addToQueue, currentQueue, transaction));
	}
	boost::shared_ptr<Connection> new_conn(new Connection(acceptor.get_io_context()));
	acceptor.async_accept(new_conn->getSocket(), boost::bind(&Server::handleAccept, this, boost::asio::placeholders::error, new_conn));
}
