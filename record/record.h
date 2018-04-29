#pragma once

#include <string>

class Record {
private:
	unsigned int index;
	unsigned long int amount;
	std::string inSig;
	std::string outSig;
public:
	Record(unsigned int, unsigned long int);
	unsigned int getIndex() const;
	void setIndex(unsigned int);
	unsigned long int getAmount() const;
	void setAmount(unsigned long int);
	std::string getInSig() const;
	void setInSig(std::string);
	std::string getOutSig() const;
	void setOutSig(std::string);
};