#include "baggage.h"


size_t baggage::get_flight_num() const
{
	return flight_num;
}

void baggage::set_flight_num(size_t flight_num)
{
	this->flight_num = flight_num;
}

std::string baggage::get_dep_date() const
{
	return dep_date;
}

void baggage::set_dep_date(const std::string& dep_date)
{
	this->dep_date = dep_date;
}

std::string baggage::get_destination() const
{
	return destination;
}

void baggage::set_destination(const std::string& destination)
{
	this->destination = destination;
}

std::string baggage::get_surname() const
{
	return surname;
}

void baggage::set_surname(const std::string& surname)
{
	this->surname = surname;
}

size_t baggage::get_baggage_num() const
{
	return baggage_num;
}

void baggage::set_baggage_num(size_t baggage_num)
{
	this->baggage_num = baggage_num;
}

size_t baggage::get_weight() const
{
	return weight;
}

void baggage::set_weight(size_t weight)
{
	this->weight = weight;
}

baggage::baggage(size_t flight_num, std::string dep_date, std::string destination, std::string surname,
	size_t baggage_num, size_t weight) : flight_num(flight_num), dep_date(dep_date), destination(destination),
	surname(surname), baggage_num(baggage_num), weight(weight)
{ }


