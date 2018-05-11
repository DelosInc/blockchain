#pragma once

#include <string>
#include <vector>
#include <chrono>

#include "record.h"

class Transaction {
private:
	std::string TID;
	std::vector<Record> recIn;
	std::vector<Record> recOut;
	unsigned long int timestamp;
public:
	std::string getTID() const;
	Record const& getRecIn(unsigned int) const;
	Record const& getRecOut(unsigned int) const;
	unsigned long int getInSum() const;
	unsigned long int getOutSum() const;
	unsigned int getRecInSize() const;
	std::string getTransactionString() const;
	void setTID(std::string);
	void setRecIn(std::vector<Record>);
	void setRecOut(std::vector<Record>);
	void setTimestamp();
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & TID;
		ar & recIn;
		ar & recOut;
		ar & timestamp;
	}
};
