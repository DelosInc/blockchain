#include "Record.h"

unsigned long int Record::getAmount() const {
	return this->amount;
}

void Record::setAmount(unsigned long int amount) {
	this->amount = amount;
}

Record::InSig Record::getInSig() const {
	return inSig;
}

void Record::setInSig(std::string sig, std::string pubKeyHash, std::string concatenatedRecord) {
	this->inSig.sig = sig;
	this->inSig.pubKey = pubKeyHash;
	this->inSig.concatenatedRecord = concatenatedRecord;
}

std::string Record::getOutSig() const {
	return this->outSig;
}

void Record::setOutSig(std::string outSig) {
	this->outSig = outSig;
}

bool Record::operator == (Record record) {
	if (this->amount == record.amount &&
		this->inSig.concatenatedRecord == record.inSig.concatenatedRecord &&
		this->inSig.pubKey == record.inSig.pubKey &&
		this->inSig.sig == record.inSig.sig &&
		this->outSig == record.outSig) {
		return true;
	}
	return false;
}