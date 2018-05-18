#pragma once

#include <exception>

class QueueEmpty :public std::exception
{
public:
	const char* what() const noexcept;
};
