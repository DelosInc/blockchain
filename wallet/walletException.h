#pragma once

#include <exception>

class AmountUnderflow :public std::exception {
public:
	const char* what() const noexcept;
};
