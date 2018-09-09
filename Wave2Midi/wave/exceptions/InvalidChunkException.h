#pragma once
#pragma once
#include <stdexcept>

class InvalidChunkException : public std::exception
{
public:
	InvalidChunkException(char* found, size_t size = 4)
	{
		_size = size;
		_found = std::string(found);
	}

	InvalidChunkException(unsigned char* found, size_t size = 4)
	{
		_size = size;
		_found = std::string((char*)found);
	}


	const char* what() const noexcept override
	{
		std::string errorString =
			std::string("[Invalid File Magic Found] No chunk with the Magic '")
			+ _found + std::string("'.");

		return errorString.c_str();
	}

private:
	size_t _size;
	std::string _found;
};
