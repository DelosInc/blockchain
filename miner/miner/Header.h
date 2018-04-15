#pragma once

#include <iostream>
#include <queue>
#include <vector>

class Miner {
private:
	std::string address;
	std::queue<Transaction> unverifiedTransactions;
	std::vector<Transaction> verifiedTransactions;
	bool verifyTransaction(Transaction);
	bool verifySig(Transaction);
	Block createBlock(vector<Transaction>);
public:
	Miner(std::string);
	void addTransaction(Transaction);
	Block mine();
};