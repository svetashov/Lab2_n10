#pragma once
#include "Utils.h"


const std::string FILE_DIRECTORY = "..\\Files\\";
const std::string FILE_EXTENSION = ".txt";

std::string& rtrim(std::string& s, const char* symbols = " :")
{
	s.erase(s.find_last_not_of(symbols) + 1);
	return s;
}

std::string& ltrim(std::string& s, const char* symbols = " :")
{
	s.erase(0, s.find_first_not_of(symbols));
	return s;
}

std::string& trim(std::string& s, const char* symbols = " :")
{
	return ltrim(rtrim(s, symbols), symbols);
}

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


std::string get_value(std::string& source, const std::string& separator)
{
	unsigned int pos = source.find(separator);
	if (pos == std::string::npos)
		pos = source.length();
	std::string result = source.substr(0, pos);
	source.erase(0, pos + separator.length());
	return trim(result);
}