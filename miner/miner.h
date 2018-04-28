#pragma once

#include <iostream>
#include <queue>
#include <vector>

class Miner {
private:
	std::string address;
	Transaction unverifiedTransaction;
	bool verifyTransaction();
	bool verifySig();
	std::vector<Transaction> verifiedTransactions;
	Block createBlock(vector<Transaction>);
public:
	Miner(std::string);
	void addTransaction();
	Block mine();
};