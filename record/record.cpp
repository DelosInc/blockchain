#include "Record.h"

Record::Record(unsigned int index, unsigned long int amount)
	: index(index),
	amount(amount) {

}

unsigned int Record::getIndex() const {
	return this->index;
}

void Record::setIndex(unsigned int index) {
	this->index = index;
}

unsigned long int Record::getAmount() const {
	return this->amount;
}

void Record::setAmount(unsigned long int amount) {
	this->amount = amount;
}

std::string Record::getInSig() const {
	return this->inSig;
}

void Record::setInSig(std::string inSig) {
	this->inSig = inSig;
}

std::string Record::getOutSig() const {
	return this->outSig;
}

void Record::setOutSig(std::string outSig) {
	this->outSig = outSig;
}