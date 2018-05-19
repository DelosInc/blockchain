#include "walletException.h"

const char* AmountUnderflow::what() const noexcept {
	return "queue_empty";
}