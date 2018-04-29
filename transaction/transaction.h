#pragma once

#include <string>
#include <vector>
#include "boost/date_time/local_time/local_time.hpp"

#include "record.h"

class Transaction {
private:
	std::string TID;
	std::vector<Record> recIn;
	std::vector<Record> recOut;
	unsigned long int timestamp;
public:
	Transaction(std::string, std::vector<Record>, std::vector<Record>);
	std::string getTID() const;
	Record const& getRecIn(unsigned int) const;
	Record const& getRecOut(unsigned int) const;
	void setTID(std::string);
	void setRecIn(Record const&, unsigned int);
	void setRecOut(Record const&, unsigned int);
	void setTimestamp();
};
