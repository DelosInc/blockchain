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
	std::chrono::time_point<std::chrono::system_clock> p2 = std::chrono::system_clock::now();
	timestamp = static_cast<unsigned long int> (std::chrono::duration_cast<std::chrono::seconds>(p2.time_since_epoch()).count());
}

void Block::setPrevBlockHash(std::string const& prevBlockHash) {
	this->prevBlockHash = prevBlockHash;
}

void Block::setBlockHash(std::string const& blockHash) {
	this->blockHash = blockHash;
}

void Block::setTransaction(Transaction const& transaction, unsigned int index) {
	this->transactions[index] = transaction;
}

void Block::setTransaction(std::vector<Transaction> const& transactions) {
	this->transactions = transactions;
}