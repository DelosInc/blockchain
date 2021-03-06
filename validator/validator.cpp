#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "server.h"
#include "blockchainHandler.h"
#include "queueHandler.h"
#include "miner.h"

static bool run;

void serving(unsigned short int port, QueueHandler *currentQueue) {
	try {
		boost::asio::io_context io_context;
		Server server(io_context, port, currentQueue);
		io_context.run();
	}
	catch (std::exception& e){
		std::cerr << e.what() << std::endl;
	}
}

void mining(std::string address, QueueHandler *currentQueue, BlockchainHandler *handler) {
	Miner miner(address, currentQueue, handler);
	std::cout << "Enter N to stop";
	while (run) {
		miner.mine();
	}
}

void control() {
	if (std::cin.get() == 'N') {
		run = false;
	}
}

int main() {
	std::string path, filename;
	std::cout << "Enter filename and path";
	std::cin >> path >> filename;
	BlockchainHandler handler(path, filename);
	QueueHandler currentQueue;
	unsigned short int port;
	std::string address;
	std::cout << "Enter the port: ";
	std::cin >> port;
	std::cout << "Enter the address: ";
	std::cin >> address;
	run = true;
	std::thread servingThread(serving, port, &currentQueue);
	std::thread controlThread(control);
	std::thread miningThread(mining, address, &currentQueue, &handler);
	servingThread.join();
	controlThread.join();
	miningThread.join();
	return 0;
}