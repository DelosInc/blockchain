#pragma once

#include <iostream>
#include <vector>

class Block {
private:
	unsigned int height;
	unsigned int timestamp;
	std::string prevBlockHash;
	std::string blockHash;
	std::string merkleRoot;
	unsigned int nonce;
	std::vector<Transaction> transactions;
public:
	Block(unsigned int, std::string const&, std::vector<Transaction> const&);
	unsigned int getHeight();
	unsigned int getTimestamp();
	std::string getPrevBlockHash();
	std::string getBlockHash();
	std::string getMerkleRoot();
	Transaction getTransaction(unsigned int);
	std::vector<Transaction> getTransaction();
	void setHeight(unsigned int);
	void setTimestamp();
	void setPrevBlockHash(std::string const&);
	void setBlockHash(std::string const&);
	void setMerkleRoot(std::string const&);
	void setNonce(unsigned int);
	void setTransaction(Transaction const&, unsigned int);
	void setTransaction(vector<Transaction> const&);
};

