#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <mutex>

#include "block.h"
#include "queueHandler.h"

class Miner {
private:
	std::string address;
	QueueHandler *currentQueue;
	std::mutex mutex;
	bool verifyTransaction();
	bool verifySig();
	void verify(Transaction&);
	std::vector<Transaction> verifiedTransactions;
	std::vector<std::thread> verifying;
	Block createBlock(std::vector<Transaction>);
public:
	Miner(std::string, QueueHandler*);
	Block mine();
};