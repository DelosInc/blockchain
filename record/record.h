#pragma once

#include <string>

class Record {
private:
	unsigned long int amount;
	struct InSig {
		std::string sig;
		std::string pubKeyHash;
	} inSig;
	std::string outSig;
public:
	unsigned long int getAmount() const;
	void setAmount(unsigned long int);
	struct InSig getInSig() const;
	void setInSig(std::string, std::string);
	std::string getOutSig() const;
	void setOutSig(std::string);
};