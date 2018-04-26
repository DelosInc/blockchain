#pragma once

#include <cassert>
#include <string>
#include <sstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <leveldb/db.h>

class BlockchainHandler
{
public:
	BlockchainHandler();
	void addBlock(Block const&);
	Block getBlock(unsigned int height);
	~BlockchainHandler();
private:
	leveldb::DB* db;
	leveldb::Options options;
	leveldb::Status status;
	std::string height;
};

