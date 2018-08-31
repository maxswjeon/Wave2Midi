/*
 * This File is part of Wav2Mid Project
 * Copyright (c) 2018 Sangwan Jeon, All Rights Reserved
 */

#define _CRT_SECURE_NO_WARNINGS

#include <fftw3.h>

#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::cout << "Wav2Mid By Sangwan Jeon" << std::endl;
	std::cout << "Wave File Path to Convert : ";

	std::string filePath;
	std::getline(std::cin, filePath);

	std::ifstream f(filePath.c_str());
	while (!f.good())
	{
		std::cout << "No file exists" << std::endl;
		std::cout << "Wave File Path to Convert : ";

		std::getline(std::cin, filePath);
		f = std::ifstream(filePath.c_str());
	}
}