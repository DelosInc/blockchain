#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <sha.h>
#include <osrng.h>
#include <hex.h>

#include "record.h"

class Transaction {
private:
	std::string TID;
	std::vector<Record> recIn;
	std::vector<Record> recOut;
	unsigned long int timestamp;
public:
	std::string getTID() const;
	Record getRecIn(unsigned int) const;
	Record getRecOut(unsigned int) const;
	unsigned long int getInSum() const;
	unsigned long int getOutSum() const;
	unsigned int getRecInSize() const;
	std::string getTransactionString() const;
	void setTID();
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
