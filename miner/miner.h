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
	bool verifyTransaction(Transaction);
	bool checkSig(Record);
	void verify(Transaction&);
	bool verifySig(std::string pubkeyStringHex, std::string message, std::string signature);
	std::vector<Transaction> verifiedTransactions;
	std::vector<std::thread> verifying;
	Block createBlock();
public:
	Miner(std::string, QueueHandler*);
	Block mine();
};