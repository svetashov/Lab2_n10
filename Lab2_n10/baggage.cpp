#include "Baggage.h"
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include "Utils.h"
#include <chrono>


Baggage::Baggage(size_t flight_num, Date dep_date, std::string destination, std::string surname,
	size_t baggage_num, size_t weight) : flight_num(flight_num), dep_date(dep_date), destination(destination),
	surname(surname), baggage_num(baggage_num), weight(weight)
{ }


std::ostream& operator<<(std::ostream& out, const Date& date)
{
	return out << date.day << "." << date.month << "." << date.year;
}

std::istream& operator>>(std::istream& in, Date& date)
{
	size_t tmp_day, tmp_month, tmp_year;
	in >> tmp_day;
	in >> tmp_month;
	in >> tmp_year;
	date = Date(tmp_day, tmp_month, tmp_year);
	return in;
}

void read(Date& date)
{
	const int year = get_number(Date::min_year, 9999, "Введите год");
	const int month = get_number(1, 12, "Введите месяц");
	const int day = get_number(1, Date::get_days_in_month(month, year), "Введите день");
	date =  { year, month, day };
}

void write(const Date& date)
{
	std::cout << date.day << "." << date.month << "." << date.year;
}

bool operator==(const Baggage a, const Baggage b)
{
	return a.flight_num == b.flight_num &&
		a.dep_date == b.dep_date &&
		a.destination == b.destination &&
		a.surname == b.surname &&
		a.baggage_num == b.baggage_num &&
		a.weight == b.weight;
}

std::ostream& operator<<(std::ostream& out, const Baggage& b)
{
	return out << b.flight_num << 
		b.dep_date << 
		b.destination <<
		b.surname << 
		b.baggage_num <<
		b.weight << std::endl << std::endl;
}

std::istream& operator>>(std::istream& in, Baggage& b)
{
	in >> b.flight_num;
	in >> b.dep_date;
	in >> b.destination;
	in >> b.surname;
	in >> b.baggage_num;
	in >> b.weight;
	std::string tmp;
	std::getline(in, tmp);
	std::getline(in, tmp);
	return in;
}

void read(Baggage& b)
{
	b.flight_num = get_number(0, SIZE_MAX, "Введите номер рейса");
	read(b.dep_date);
	b.destination = get_string(1, "Введите пункт назначения");
	b.surname = get_string(1, "Введите фамилию");
	b.flight_num = get_number(1, SIZE_MAX, "Введите количество багажа");
	b.weight = get_number(1, SIZE_MAX, "Введите вес багажа");
}

void write(const Baggage& b)
{
	std::cout << std::setw(8) << b.flight_num << std::setw(1) << "|";
	write(b.dep_date);
	std::cout << std::setw(1) << "|";
	std::cout << std::setw(8) << b.destination << std::setw(1) << "|" <<
		std::setw(8) << b.surname << std::setw(1) << "|" <<
		std::setw(8) << b.flight_num << std::setw(1) << "|" <<
		std::setw(8) << b.weight << std::endl;
}

Date::Date() : year(min_year), month(min_month), day(min_day)
{
};

Date::Date(const int year, const int month, const int day)
{
	if (year < min_year)
		throw std::runtime_error("Некорректное значение для года.");
	if (month < 1 || month > 12)
		throw std::runtime_error("Некорректное значение для месяца.");
	if (day < 1 || day > get_days_in_month(month, year))
		throw std::runtime_error("Некорректное значение для дня.");
	this->year = year;
	this->month = month;
	this->day = day;
}


bool Date::operator==(const Date& rvalue) const
{
	return year == rvalue.year && day == rvalue.day && month == rvalue.month;
}

bool Date::is_leap(const int year)
{
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int Date::get_days_in_month(const int month, const int year)
{
	switch (month)
	{
	case 2:
		return 28 + is_leap(year);
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	default:
		return 0;
	}
}
