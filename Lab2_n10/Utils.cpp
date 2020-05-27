#pragma once
#include "Utils.h"


const std::string FILE_DIRECTORY = "..\\Files\\";
const std::string FILE_EXTENSION = ".txt";

int32_t get_number(int32_t min, int32_t max, const std::string& message)
{
	int32_t result;
	std::string tmp;
	bool check;
	do
	{
		std::cout << message << " [" << min << ", " << max << "]: ";
		std::cin >> result;
		if (std::cin.fail())
			std::cin.clear();
		getline(std::cin, tmp);
		check = (result >= min) && (result <= max);
		if (!check)
			std::cout << "����� ������� �� ������� ���������! ��������� ����." << std::endl;
	}
	while (!check);
	return result;
}

bool get_answer(const std::string& message)
{
	int32_t result;
	std::string tmp;
	bool check;
	do
	{
		std::cout << message << " (1 - ��, 0 - ���): ";
		std::cin >> result;
		getline(std::cin, tmp);
		check = (result >= 0) && (result <= 1);
		if (!check)
			std::cout << "����� ������� �� ������� ���������! ��������� ����." << std::endl;
	}
	while (!check);
	return (result == 1);
}

std::string get_string(int32_t min_length, const std::string& message)
{
	std::string result;
	std::string tmp;
	bool check;
	do
	{
		std::cout << message << ": ";
		std::cin >> result;
		getline(std::cin, tmp);
		check = result.length() >= min_length;
		if (!check)
			std::cout << "������������� ����� ��������� ������, ������� ������ (����������� ����� " << min_length <<
				")." << std::endl;
	}
	while (!check);
	return result;
}

std::string get_filename(const std::string& message)
{
	std::string filename;
	std::string tmp;
	std::cout << message << ": ";
	std::cin >> filename;
	getline(std::cin, tmp);
	return filename;
}

std::string get_filepath(const std::string& filename)
{
	return (FILE_DIRECTORY + filename + FILE_EXTENSION);
}
