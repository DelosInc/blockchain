#include <stack>
#include "Miner.h"
#include "C:\crypto++\sha.h"

Miner::Miner(std::string address)
	:address(address) {

}

void Miner::addTransaction() {
	unverifiedTransaction = Server::getTransaction();
}

bool Miner::verifyTransaction() {
	if ((unverifiedTransaction.getInSum() < unverifiedTransaction.getOutSum()) ||
		unverifiedTransaction.getInSum() == 0 || unverifiedTransaction.getOutSum() == 0) {
		return false;
	}
	if (!verifiedTransactions.empty()) {
		for (int recIn_i = 0; recIn_i < unverifiedTransaction.getInSize(); recIn_i++) {
			for (int verified_i = 0; verified_i < verifiedTransactions.size(); verified_i++) {
				for (int recOut_j = 0; recOut_j < 2; recOut_j++) {
					if (unverifiedTransaction.getRecIn(recIn_i) ==
						verifiedTransaction[verified_i].getRecOut(recOut_j)) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool Miner::verifySig() {
	//check signatures
}

Block Miner::mine() {
	while(verifiedTransactions.size!=5) {
		if (verifyTransaction() && verifySig()) {
			verifiedTransactions.push_back(unverifiedTransaction);
		}
		addTransaction();
	}
	verifiedTransactions.push_back(coinbaseTransaction);
	Block block = createBlock(verifiedTransactions);
	return block;
}