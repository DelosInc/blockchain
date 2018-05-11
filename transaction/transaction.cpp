#include "transaction.h"

std::string Transaction::getTID() const {
	return TID;
}

Record const& Transaction::getRecIn(unsigned int index) const {
	return recIn[index];
}

Record const& Transaction::getRecOut(unsigned int index) const {
	return recOut[index];
}

unsigned long int Transaction::getInSum() const {
	unsigned long int inSum = 0;
	for (std::vector<Record>::const_iterator it = recIn.begin(); it != recIn.end(); ++it) {
		inSum += it->getAmount();
	}
	return inSum;
}

unsigned long int Transaction::getOutSum() const {
	unsigned long int outSum = 0;
	for (std::vector<Record>::const_iterator it = recOut.begin(); it != recOut.end(); ++it) {
		outSum += it->getAmount();
	}
	return outSum;
}

unsigned int Transaction::getRecInSize() const {
	return recIn.size();
}

std::string Transaction::getTransactionString() const {
	std::string transactionString;
	for (std::vector<Record>::const_iterator it = recIn.begin(); it != recIn.end(); ++it){
		transactionString = transactionString + std::to_string(it->getAmount()) + it->getInSig().sig
			+ it->getInSig().pubKey + it->getOutSig();
	}
	for (std::vector<Record>::const_iterator it = recOut.begin(); it != recOut.end(); ++it) {
		transactionString = transactionString + std::to_string(it->getAmount()) + it->getOutSig();
	}
	transactionString = transactionString + std::to_string(timestamp);
	return transactionString;
}

void Transaction::setTID(std::string TID) {
	this->TID = TID;
}

void Transaction::setRecIn(std::vector<Record> recIn) {
	this->recIn = recIn;
}

void Transaction::setRecOut(std::vector<Record> recOut) {
	this->recOut = recOut;
}

void Transaction::setTimestamp() {
	std::chrono::time_point<std::chrono::system_clock> p2 = std::chrono::system_clock::now();
	timestamp = static_cast<unsigned long int> (std::chrono::duration_cast<std::chrono::seconds>(p2.time_since_epoch()).count());
}
