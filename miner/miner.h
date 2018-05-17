#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <mutex>
#include <stack>
#include <hex.h>
#include <osrng.h>
#include <pssr.h>
#include <rsa.h>
#include <sha.h>

#include "block.h"
#include "record.h"
#include "queueHandler.h"
#include "coinbaseTransaction.h"
#include "blockchainHandler.h"

class Miner {
private:
	std::string address;
	QueueHandler *currentQueue;
	BlockchainHandler* handler;
	std::mutex mutex;
	bool verifyTransaction(Transaction);
	bool checkSig(Record);
	void verify(Transaction&);
	bool verifySig(Record);
	std::vector<Transaction> verifiedTransactions;
	std::vector<std::thread> verifying;
	Transaction coinbase();
	void createBlock();
public:
	Miner(std::string, QueueHandler*, BlockchainHandler*);
	Block mine();
};