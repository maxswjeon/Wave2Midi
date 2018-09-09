#pragma once
#pragma once
#include <stdexcept>

class EmptyListException : std::exception
{
public:
	EmptyListException()
	{
	}
};
