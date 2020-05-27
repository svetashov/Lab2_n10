#pragma once
#include <string>

struct Date
{
public:
	int year;
	int month;
	int day;

	static const int min_year = 1970;
	static const int min_month = 1;
	static const int min_day = 1;

	Date();
	Date(int year, int month, int day);
	bool operator==(const Date& rvalue) const;
	friend std::ostream& operator<< (std::ostream& out, const Date& date);
	friend std::istream& operator>> (std::istream& in, Date& date);
	friend void read(Date& date);
	friend void write(const Date& date);

private:
	static bool is_leap(int year);
	static int get_days_in_month(int month, int year);
};

struct Baggage
{
	
	Baggage(size_t flight_num = 0, Date dep_date = Date(),
	        std::string destination = "", std::string surname = "",
	        size_t baggage_num = 0, size_t weight = 0);
	friend bool operator==(const Baggage a, const Baggage b);
	friend std::ostream& operator<< (std::ostream& out, const Baggage& b);
	friend std::istream& operator>> (std::istream& in, Baggage& b);
	friend void read(Baggage& b);
	friend void write(const Baggage& b);

	size_t flight_num;
	Date dep_date;
	std::string destination;
	std::string surname;
	size_t baggage_num;
	size_t weight;
};
