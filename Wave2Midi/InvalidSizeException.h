#pragma once
#include <stdexcept>

class InvalidSizeException : std::runtime_error
{
public:
	InvalidSizeException(size_t expect, size_t found) : std::runtime_error("Invalid File Size Found")
	{
		_expect = expect;
		_found = found;
	}

	const char* what() const override
	{
		std::string errorString = std::string("File Size Expected to be bigger than ");
		errorString += _expect;
		errorString += "bytes, Found ";
		errorString += _found;
		errorString += "bytes.";
		return errorString.c_str();
	}

private:
	size_t _expect;
	size_t _found;
};
