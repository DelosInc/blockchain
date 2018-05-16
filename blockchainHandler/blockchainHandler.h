#pragma once

#include <cassert>
#include <string>
#include <sstream>
#include <list>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "myDB.h"
#include "block.h"

class BlockchainHandler {
private:
	myDB db;
	unsigned int height;
public:
	BlockchainHandler();
	void addBlock(Block const&);
	Block getBlock(unsigned int height);
	unsigned int getHeight();
	std::string getBlockHash();
};

