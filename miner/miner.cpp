#include <stack>
#include <hex.h>
#include <osrng.h>
#include <pssr.h>
#include <rsa.h>
#include <sha.h>
#include "Miner.h"


Miner::Miner(std::string address, QueueHandler *currentQueue)
	:address(address),
	currentQueue(currentQueue) {

}

bool Miner::verifyTransaction() {
	if ((unverifiedTransaction.getInSum() < unverifiedTransaction.getOutSum()) ||
		unverifiedTransaction.getInSum() == 0 || unverifiedTransaction.getOutSum() == 0) {
		return false;
	}
	if (!verifiedTransactions.empty()) {
		for (int recIn_i = 0; recIn_i < unverifiedTransaction.getRecInSize(); recIn_i++) {
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

bool Miner::checkSig(Record record) {
	std::string pubKey = record.getInSig().pubKey;
	std::string pubKeyHash;
}

bool Miner::verifySig(std::string pubkeyStringHex, std::string message, std::string signature) {
	using Verifier = CryptoPP::RSASS<CryptoPP::PSSR, CryptoPP::SHA256>::Verifier;

	CryptoPP::RSA::PublicKey publicKey;
	publicKey.Load(CryptoPP::StringSource(pubkeyStringHex, true, new CryptoPP::HexDecoder()).Ref());

	std::string decodedSignature;
	CryptoPP::StringSource ss(signature, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decodedSignature)));

	bool result = false;
	Verifier verifier(publicKey);
	CryptoPP::StringSource ss2(decodedSignature + message, true,
		new CryptoPP::SignatureVerificationFilter(verifier,
			new CryptoPP::ArraySink((CryptoPP::byte*)&result,
				sizeof(result))));
	return result;
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