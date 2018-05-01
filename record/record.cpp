#include "Record.h"

unsigned long int Record::getAmount() const {
	return this->amount;
}

void Record::setAmount(unsigned long int amount) {
	this->amount = amount;
}

struct InSig Record::getInSig() const {
	return inSig;
}

void Record::setInSig(std::string sig, std::string pubKeyHash) {
	this->inSig.sig = sig;
	this->inSig.pubKeyHash = pubKeyHash;
}

std::string Record::getOutSig() const {
	return this->outSig;
}

void Record::setOutSig(std::string outSig) {
	this->outSig = outSig;
}