#pragma once

#include <queue>
#include <mutex>

#include "queueException.h"
#include "transaction.h"

class QueueHandler {
public:
	void addToQueue(Transaction&);
	bool isEmpty();
	Transaction getTransaction();
private:
	std::queue <Transaction> pool;
	std::mutex mutex;
};
