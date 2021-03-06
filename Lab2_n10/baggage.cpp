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
	if (!in.eof())
	{
		std::string tmp;
		in >> tmp;
		const std::string separator = ".";
		const int day = std::stoi(get_value(tmp, separator));
		const int month = std::stoi(get_value(tmp, separator));
		const int year = std::stoi(get_value(tmp, separator));
		
		date = { year, month, day };
	}
	

	return in;
}

void read(Date& date)
{
	const int year = get_number(Date::min_year, 9999, "������� ���");
	const int month = get_number(1, 12, "������� �����");
	const int day = get_number(1, Date::get_days_in_month(month, year), "������� ����");
	date =  { year, month, day };
}

void write(const Date& date)
{
	std::cout << " " << std::setfill('0') << std::setw(2) << date.day << std::setw(1) << "." <<
		std::setw(2) << date.month << std::setw(1) << "." <<
		std::setw(4) << date.year << std::setfill(' ');
}

int compare(const Date& d1, const Date& d2)
{
	if (d1.year > d2.year)
		return 1;
	if (d1.year < d2.year)
		return -1;
	if (d1.month > d2.month)
		return 1;
	if (d1.month < d2.month)
		return -1;
	if (d1.day > d2.day)
		return 1;
	if (d1.day < d2.day)
		return -1;
	return 0;
}

int compare(const int x, const int y)
{
	if (x > y)
		return 1;
	if (x < y)
		return -1;
	return 0;
}

int compare(const std::string& x, const std::string& y)
{
	return x.compare(y);
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
	return out << b.flight_num << std::endl <<
		b.dep_date << std::endl <<
		b.destination << std::endl <<
		b.surname << std::endl <<
		b.baggage_num << std::endl <<
		b.weight << std::endl;
}

std::istream& operator>>(std::istream& in, Baggage& b)
{
	in >> b.flight_num;
	in >> b.dep_date;
	in >> b.destination;
	in >> b.surname;
	in >> b.baggage_num;
	in >> b.weight;
	
	return in;
}

void read(Baggage& b)
{
	b.flight_num = get_number(0, INT32_MAX, "������� ����� �����");
	read(b.dep_date);
	b.destination = get_string(1, "������� ����� ����������");
	b.surname = get_string(1, "������� �������");
	b.baggage_num = get_number(1, INT32_MAX, "������� ���������� ������");
	b.weight = get_number(1, INT32_MAX, "������� ��� ������");
}

void write(const Baggage& b)
{
	std::cout << std::setw(11) << b.flight_num << std::setw(1) << "|";
	write(b.dep_date);
	std::cout << std::setw(1) << "|";
	std::cout << std::setw(16) << b.destination << std::setw(1) << "|" <<
		std::setw(11) << b.surname << std::setw(1) << "|" <<
		std::setw(6) << b.baggage_num << std::setw(1) << "|" <<
		std::setw(5) << b.weight << "|" << std::endl;
}

Date::Date() : year(min_year), month(min_month), day(min_day)
{
};

Date::Date(const int year, const int month, const int day)
{
	if (year < min_year)
		throw std::runtime_error("������������ �������� ��� ����.");
	if (month < 1 || month > 12)
		throw std::runtime_error("������������ �������� ��� ������.");
	if (day < 1 || day > get_days_in_month(month, year))
		throw std::runtime_error("������������ �������� ��� ���.");
	this->year = year;
	this->month = month;
	this->day = day;
}


bool Date::operator==(const Date& rvalue) const
{
	return compare(*this, rvalue) == 0;
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
