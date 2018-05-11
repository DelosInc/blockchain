#pragma once

#include <string>
#include <vector>
#include <chrono>

#include "transaction.h"

class Block {
private:
	unsigned int height;
	unsigned int timestamp;
	std::string prevBlockHash;
	std::string blockHash;
	std::vector<Transaction> transactions;
public:
	Block() = default;
	Block(unsigned int, std::string const&, std::vector<Transaction> const&);
	unsigned int getHeight();
	unsigned int getTimestamp();
	std::string getPrevBlockHash();
	std::string getBlockHash();
	Transaction getTransaction(unsigned int);
	std::vector<Transaction> getTransaction();
	void setHeight(unsigned int);
	void setTimestamp();
	void setPrevBlockHash(std::string const&);
	void setBlockHash(std::string const&);
	void setTransaction(Transaction const&, unsigned int);
	void setTransaction(std::vector<Transaction> const&);
};

