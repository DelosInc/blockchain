#include "block.h"

Block::Block(unsigned int height, std::string const& prevBlockHash, std::vector<Transaction> const& transactions)
	: height(height),
	prevBlockHash(prevBlockHash),
	transactions(transactions) {

}

unsigned int Block::getHeight() {
	return height;
}

unsigned int Block::getTimestamp() {
	return timestamp;
}

std::string Block::getPrevBlockHash() {
	return prevBlockHash;
}

std::string Block::getBlockHash() {
	return blockHash;
}

std::string Block::getMerkleRoot() {
	return merkleRoot;
}

Transaction Block::getTransaction(unsigned int index) {
	return transactions[index];
}

std::vector<Transaction> Block::getTransaction() {
	return transactions;
}

void Block::setHeight(unsigned int height) {
	this->height = height;
}

void Block::setTimestamp() {
	boost::posix_time::ptime time_t_local = boost::posix_time::second_clock::local_time();
	boost::posix_time::ptime time_t_epoch(date(1970, 1, 1));
	timestamp = time_t_local - time_t_epoch;
}

void Block::setPrevBlockHash(std::string const& prevBlockHash) {
	this->prevBlockHash = prevBlockHash;
}

void Block::setBlockHash(std::string const& blockHash) {
	this->blockHash = blockHash;
}

void Block::setMerkleRoot(std::string const& merkleRoot) {
	this->merkleRoot = merkleRoot;
}

void Block::setNonce(unsigned int nonce) {
	this->nonce = nonce;
}

void Block::setTransaction(Transaction const& transaction, unsigned int index) {
	this->transactions[index] = transaction;
}

void Block::setTransaction(std::vector<Transaction> const& transactions) {
	this->transactions = transactions;
}