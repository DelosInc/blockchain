#pragma once

#include <iostream>
#include <queue>
#include <vector>

#include "block.h"

class Miner {
private:
	std::string address;
	Transaction unverifiedTransaction;
	bool verifyTransaction();
	bool verifySig();
	std::vector<Transaction> verifiedTransactions;
	Block createBlock(std::vector<Transaction>);
public:
	Miner(std::string);
	void addTransaction();
	Block mine();
};