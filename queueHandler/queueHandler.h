#pragma once

#include <queue>

#include "transaction.h"

class QueueHandler {
public:
	void addToQueue(Transaction&);
	Transaction getTransaction();
private:
	std::queue <Transaction> pool;
};
