#include <stack>
#include "Miner.h"
#include "sha.h"

Miner::Miner(std::string address, QueueHandler *currentQueue)
	:address(address),
	currentQueue(currentQueue){

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
	while (1) {
		if (!currentQueue->isEmpty()) {
			verifying.push_back(std::thread(&Miner::verify, this, currentQueue->getTransaction()));
		}
		if (verifiedTransactions.size == 5) {
			createBlock();
		}
	}
}

void Miner::verify(Transaction& transaction) {
	if (verifyTransaction(transaction) && verifySig(transaction)) {
		mutex.lock();
		verifiedTransactions.push_back(transaction);
		mutex.unlock();
	}
}