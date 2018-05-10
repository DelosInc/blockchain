#pragma once

#include <cassert>
#include <string>
#include <sstream>
#include <list>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <leveldb/db.h>

#include "block.h"

class BlockchainHandler
{
public:
	BlockchainHandler();
	void addBlock(Block const&);
	~BlockchainHandler();
private:
	leveldb::DB* db;
	leveldb::Options options;
	leveldb::Status status;
	std::string height;
	std::list <Block> blockchain;
	Block getBlock(unsigned int height);
	void initList(unsigned int=1);
};

