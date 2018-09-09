#pragma once
#include <stdexcept>

class InvalidMagicException : public std::exception
{
public:
	InvalidMagicException(char* expect, char* found, size_t size = 4) : std::exception("Invalid File Magic Found")
	{
		_size = size;
		_expect = std::string(expect);
		_found = std::string(found);
	}

	InvalidMagicException(unsigned char* expect, unsigned char* found, size_t size = 4) : std::exception("Invalid File Magic Found")
	{
		_size = size;
		_expect = std::string((char*)expect);
		_found = std::string((char*)found);
	}

	InvalidMagicException(const char* expect, char* found, size_t size = 4) : std::exception("Invalid File Magic Found")
	{
		_size = size;
		_expect = std::string(expect);
		_found = std::string(found);
	}

	InvalidMagicException(const unsigned char* expect, unsigned char* found, size_t size = 4) : std::exception("Invalid File Magic Found")
	{
		_size = size;
		_expect = std::string((char*)expect);
		_found = std::string((char*)found);
	}

	const char* what() const noexcept override
	{
		std::string errorString = 
			std::string("[Invalid File Magic Found] File Magic Expected to be ") 
			+ _expect + std::string(", Found ") 
			+ _found + std::string(".");

		return errorString.c_str();
	}

private:
	size_t _size;
	std::string _expect;
	std::string _found;
};
