#pragma once

#include <cassert>
#include <string>
#include <sstream>
#include <list>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <db_cxx.h>

#include "block.h"

class BlockchainHandler {
private:
	Db db;
	std::string dbFileName;
	u_int32_t cFlags;
	unsigned int height;
public:
	BlockchainHandler(std::string, std::string);
	BlockchainHandler();
	void addBlock(Block const&);
	Block getBlock(unsigned int height);
	unsigned int getHeight();
	std::string getBlockHash();
};

