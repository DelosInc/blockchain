#include "Miner.h"


Miner::Miner(std::string address, QueueHandler *currentQueue)
	:address(address),
	currentQueue(currentQueue) {

}

bool Miner::verifyTransaction(Transaction transaction) {
	if ((transaction.getInSum() < transaction.getOutSum()) ||
		transaction.getInSum() == 0 || transaction.getOutSum() == 0) {
		return false;
	}
	if (!verifiedTransactions.empty()) {
		for (int recIn_i = 0; recIn_i < transaction.getRecInSize(); recIn_i++) {
			for (int verified_i = 0; verified_i < verifiedTransactions.size(); verified_i++) {
				for (int recOut_j = 0; recOut_j < 2; recOut_j++) {
					if (transaction.getRecIn(recIn_i) ==
						verifiedTransactions[verified_i].getRecOut[recOut_j]) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool Miner::checkSig(Record record) {
	CryptoPP::SHA256 hash;
	std::string pubKey = record.getInSig().pubKey;
	std::string digest;
	CryptoPP::StringSource s(pubKey, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
	if (digest == record.getOutSig()) {
		return true;
	}
	return false;
}

bool Miner::verifySig(Record record) {
	using Verifier = CryptoPP::RSASS<CryptoPP::PSSR, CryptoPP::SHA256>::Verifier;

	CryptoPP::RSA::PublicKey publicKey;
	publicKey.Load(CryptoPP::StringSource(record.getInSig().pubKey, true, new CryptoPP::HexDecoder()).Ref());

	std::string decodedSignature;
	CryptoPP::StringSource ss(record.getInSig().sig, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decodedSignature)));

	bool result = false;
	Verifier verifier(publicKey);
	CryptoPP::StringSource ss2(decodedSignature + record.getInSig().concatenatedRecord, true,
		new CryptoPP::SignatureVerificationFilter(verifier,
			new CryptoPP::ArraySink((CryptoPP::byte*)&result,
				sizeof(result))));
	return result;
}

Block Miner::mine() {
	for (std::vector<std::thread>::iterator it = verifying.begin(); it != verifying.end(); ++it) {
		if (it->joinable()) {
			it->join();
		}
	}
	verifying.clear();
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
	if (verifyTransaction(transaction)) {
		bool flag = true;
		for(unsigned int i=0;i<transaction.getRecInSize();i++){
			if (!verifySig(transaction.getRecIn(i))) {
				flag = true;
				break;
			}
		}
		if (flag) {
			mutex.lock();
			verifiedTransactions.push_back(transaction);
			mutex.unlock();
		}
	}
}