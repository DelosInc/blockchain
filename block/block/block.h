#pragma once

#include <iostream>
#include <vector>

class block {
private:
	unsigned int height;
	unsigned int timestamp;
	std::string prevBlockHash;
	std::string blockHash;
	std::string merkleRoot;
	unsigned int nonce;
	std::vector<Transaction> transactions;
public:
	block();
	~block();
};

