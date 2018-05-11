#pragma once

#include <string>

class Record {
private:
	unsigned long int amount;
	struct InSig {
		std::string sig;
		std::string pubKey;
		std::string concatenatedRecord;
	} inSig;
	std::string outSig;
public:
	unsigned long int getAmount() const;
	void setAmount(unsigned long int);
	InSig getInSig() const;
	void setInSig(std::string, std::string, std::string);
	std::string getOutSig() const;
	void setOutSig(std::string);
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & amount;
		ar & inSig.sig;
		ar & inSig.pubKey;
		ar & inSig.concatenatedRecord;
		ar & outSig;
	}
};