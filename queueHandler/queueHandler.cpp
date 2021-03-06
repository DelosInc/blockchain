#include "queueHandler.h"

void QueueHandler::addToQueue(Transaction &transaction) {
	mutex.lock();
	pool.push(transaction);
	mutex.unlock();
}

Transaction QueueHandler::getTransaction() {
	if (!pool.empty()) {
		mutex.lock();
		Transaction toBeMined = pool.front();
		pool.pop();
		mutex.unlock();
		return toBeMined;
	}
	throw QueueEmpty();
}

bool QueueHandler::isEmpty() {
	return pool.empty();
}