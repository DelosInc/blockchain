#include <stack>
#include "Miner.h"
#include "C:\crypto++\sha.h"

Miner::Miner(std::string address)
	:address(address) {

}

void Miner::addTransaction(Transaction transaction) {
	unverifiedTransactions.push(transaction);
}

bool Miner::verifyTransaction(Transaction transaction) {
	if ((transaction.getInSum() < transaction.getOutSum()) ||
		transaction.getInSum() == 0 || transaction.getOutSum() == 0) {
		return false;
	}
	if (!verifiedTransactions.empty()) {
		for (int recIn_i = 0; recIn_i < transaction.getInSize(); recIn_i++) {
			for (int verified_i = 0; verified_i < verifiedTransactions.size(); verified_i++) {
				for (int recOut_j = 0; recOut_j < 2; recOut_j++) {
					if (transaction.getRecIn(recIn_i) ==
						verifiedTransaction[verified_i].getRecOut(recOut_j)) {
						return false;
					}
				}
			}
		}
	}
}

bool Miner::verifySig(Transaction transaction) {
	for (int recIn_i = 0; recIn_i < transaction.getInSize(); recIn_i++) {
		std::string pubKey = transaction.getRecIn(i).getInSig().pubKey;
		std::string digest;
		CryptoPP::SHA256 pubKeyHash;
		CryptoPP::StringSource foo(pubKey, true,
			new CryptoPP::HashFilter(pubKeyHash,
				new CryptoPP::Base64Encoder(
					new CryptoPP::StringSink(digest))));
		if (pubKeyHash != transaction.getRecIn(i).getOutSig()) {
			return false;
		}
		pubKeySig =
	}
}
