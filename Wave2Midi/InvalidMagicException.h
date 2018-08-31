#pragma once
#include <stdexcept>

class InvalidMagicException : std::runtime_error
{
public:
	InvalidMagicException(char* expect, char* found) : std::runtime_error("Invalid File Magic Found")
	{
		_expect = std::string(expect);
		_found = std::string(found);
	}

	const char* what() const override
	{
		std::string errorString = std::string("File Magic Expected to be ") + _expect + std::string(", Found ") + _found + std::string(".");
		return errorString.c_str();
	}

private:
	std::string _expect;
	std::string _found;
};
