#pragma once

#include <iostream>
#include <queue>
#include <vector>

#include "block.h"
#include "queueHandler.h"

class Miner {
private:
	std::string address;
	Transaction unverifiedTransaction;
	QueueHandler *currentQueue;
	bool verifyTransaction();
	bool verifySig();
	std::vector<Transaction> verifiedTransactions;
	Block createBlock(std::vector<Transaction>);
public:
	Miner(std::string, QueueHandler*);
	void addTransaction();
	Block mine();
};