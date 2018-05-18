#include "BlockchainHandler.h"

BlockchainHandler::BlockchainHandler(std::string path, std::string filename)
	: db(NULL, 0),
	dbFileName(path + dbFileName),
	cFlags(DB_CREATE) {
	try {
		db.set_error_stream(&std::cerr);
		db.open(NULL, dbFileName.c_str(), NULL, DB_QUEUE, cFlags, 0);
	}
	catch (DbException &e) {
		std::cerr << "Error opening database\n";
		std::cerr << e.what() << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Error opening database\n";
		std::cerr << e.what() << std::endl;
	}
	Dbc *iterator;
	Dbt key, value;
	db.cursor(NULL, &iterator, 0);
	iterator->get(&key, &value, DB_LAST);
	height = *static_cast<int*> (key.get_data());
}

void BlockchainHandler::addBlock(Block const& block) {
	height++;
	Dbt key(&height, sizeof(height));
	Dbt value(static_cast<void*> (const_cast<Block*> (&block)), sizeof(block));
	int ret = db.put(NULL, &key, &value, DB_NOOVERWRITE);
	if (ret == DB_KEYEXIST) {
		db.err(ret, "Write failed since key already exists");
	}
}

Block BlockchainHandler::getBlock(unsigned int height) {
	Dbt key(&height, sizeof(height)), value;
	db.get(NULL, &key, &value, 0);
	Block *block = reinterpret_cast<Block*> (value.get_data());
	return *block;
}

unsigned int BlockchainHandler::getHeight() {
	return height;
}

std::string BlockchainHandler::getBlockHash() {
	Dbt key(&height, sizeof(height)), value;
	db.get(NULL, &key, &value, 0);
	Block *block = reinterpret_cast<Block*> (value.get_data());
	return block->getBlockHash();
}

BlockchainHandler::~BlockchainHandler() {
	try {
		db.close(0);
		std::cout << "Database closed";
	}
	catch (DbException &e) {
		std::cerr << "Error closing database\n";
		std::cerr << e.what() << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Error closing database\n";
		std::cerr << e.what() << std::endl;
	}
}