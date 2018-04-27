#include "transaction.h"
#include "boost/date_time/local_time/local_time.hpp"

Transaction::Transaction(std::string TID, std::vector<Record> recIn, std::vector<Record>recOut)
	: TID(TID),
	recIn(recIn),
	recOut(recOut) {

}

std::string Transaction::getTID() const {
	return TID;
}

Record const& Transaction::getRecIn(unsigned int index) const {
	return recIn[index];
}

Record const& Transaction::getRecOut(unsigned int index) const {
	return recOut[index];
}

void Transaction::setTID(std::string TID) {
	this->TID = TID;
}

void Transaction::setRecIn(Record const& recIn, unsigned int index) {
	this->recIn[index] = recIn;
}

void Transaction::setRecOut(Record const& recOut, unsigned int index) {
	this->recOut[index] = recOut;
}

void Transaction::setTimestamp() {
	boost::posix_time::ptime time_t_local = boost::posix_time::second_clock::local_time();
	boost::posix_time::ptime time_t_epoch(date(1970, 1, 1));
	timestamp = time_t_local - time_t_epoch;
}