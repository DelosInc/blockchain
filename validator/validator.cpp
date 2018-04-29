#include <iostream>
#include <exception>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include "Server.h"

int main(int argc, char* argv[]) {
	try {
		if (argc != 2) {
			std::cerr << "Usage: server <port>" << std::endl;
			return 1;
		}
		boost::asio::io_context io_context;
		Server server(io_context, boost::lexical_cast<unsigned short>(argv[1]));
		io_context.run();

	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}