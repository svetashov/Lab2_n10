#pragma once
#include "Utils.h"


const std::string FILE_DIRECTORY = "..\\Files\\";
const std::string FILE_EXTENSION = ".txt";

int32_t get_number(int32_t min, int32_t max, const std::string& message)
{
	int rv = 0;
	std::string tmp;
	bool correct;
	std::cout << message << " --> ";
	do
	{
		correct = true;
		std::cin >> tmp;
		try
		{
			rv = std::stoi(tmp);
		}
		catch (std::exception&)
		{
			correct = false;
		}
		if (!correct || rv < min || rv > max)
			std::cout << "Ошибка, введите снова --> ";
	} while (!correct || rv < min || rv > max);
	return rv;
}

bool get_answer(const std::string& message)
{
	int32_t result;
	std::string tmp;
	bool check;
	do
	{
		std::cout << message << " (1 - да, 0 - нет): ";
		std::cin >> result;
		getline(std::cin, tmp);
		check = (result >= 0) && (result <= 1);
		if (!check)
			std::cout << "Число выходит за границы диапазона! Повторите ввод." << std::endl;
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
			std::cout << "Недостаточная длина введенной строки, введите заново (минимальная длина " << min_length <<
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
