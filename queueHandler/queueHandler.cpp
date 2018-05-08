#include "queueHandler.h"

void QueueHandler::addToQueue(Transaction &transaction) {
	pool.push(transaction);
}

Transaction QueueHandler::getTransaction() {
	if (!pool.empty()) {
		Transaction toBeMined = pool.front();
		pool.pop();
		return toBeMined;
	}
}