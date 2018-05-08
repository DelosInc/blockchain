#pragma once

#include <queue>
#include <mutex>

#include "transaction.h"

class QueueHandler {
public:
	void addToQueue(Transaction&);
	Transaction getTransaction();
private:
	std::queue <Transaction> pool;
	std::mutex mutex;
};
