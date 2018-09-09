#pragma once
#include <stdexcept>

class InvalidSizeException : std::exception
{
public:
	InvalidSizeException(size_t expect, size_t found) : std::exception("Invalid File Size Found")
	{
		_expect = expect;
		_found = found;
	}

	const char* what() const noexcept override
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
