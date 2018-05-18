#include "queueException.h"

const char* QueueEmpty::what() const noexcept {
	return "queue_empty";
}