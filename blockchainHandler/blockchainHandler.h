#pragma once

#include <cassert>
#include <string>
#include <sstream>
#include <list>
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
	void addBlock(Block const&);
	Block getBlock(unsigned int height);
	unsigned int getHeight();
	std::string getBlockHash();
};

