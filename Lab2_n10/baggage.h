#pragma once
#include <string>

class baggage
{
public:
	size_t get_flight_num() const;
	void set_flight_num(size_t flight_num);
	std::string get_dep_date() const;
	void set_dep_date(const std::string& dep_date);
	std::string get_destination() const;
	void set_destination(const std::string& destination);
	std::string get_surname() const;
	void set_surname(const std::string& surname);
	size_t get_baggage_num() const;
	void set_baggage_num(size_t baggage_num);
	size_t get_weight() const;
	void set_weight(size_t weight);
	baggage(size_t flight_num = 0, std::string dep_date = "",
	        std::string destination = "", std::string surname = "",
	        size_t baggage_num = 0, size_t weight = 0);

private:
	size_t flight_num;
	std::string dep_date;
	std::string destination;
	std::string surname;
	size_t baggage_num;
	size_t weight;
};
