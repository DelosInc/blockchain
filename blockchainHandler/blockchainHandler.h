#pragma once

#include <cassert>
#include <string>
#include <sstream>
#include <list>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "DB.h"
#include "block.h"

class BlockchainHandler {
private:
	DB db;
	std::string height;
	std::list <Block> blockchain;
	void initList(unsigned int = 1);
public:
	BlockchainHandler();
	void addBlock(Block const&);
	Block getBlock(unsigned int height);
	unsigned int getHeight();
	std::string getBlockHash();
	~BlockchainHandler();

};

