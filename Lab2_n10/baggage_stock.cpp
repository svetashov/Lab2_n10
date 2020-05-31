#include "baggage_stock.h"
#include <algorithm>
#include <stdexcept>
#include <streambuf>
#include <iterator>
#include <numeric>
#include <iomanip>
#include <vector>

baggage_stock::baggage_stock()
{
	baggages_ = std::vector<Baggage>();
}

void baggage_stock::add(const Baggage& b)
{
	if (contains(b.flight_num))
		throw new std::invalid_argument("������ ����� ��� ��������.");
	baggages_.push_back(b);
}

void baggage_stock::update(const Baggage& b)
{
	const auto it = std::find_if(baggages_.begin(), baggages_.end(), [&b](const Baggage& other)
		{
			return other.flight_num == b.flight_num;
		});
	if (it == baggages_.end())
		throw std::invalid_argument("����� �� ������ � ����.");
	*it = b;
}

bool baggage_stock::remove(size_t flight_num)
{
	const auto it = std::remove_if(baggages_.begin(), baggages_.end(),
		[&flight_num](Baggage& other) { return flight_num == other.flight_num; });
	const bool result = it != baggages_.end();
	if (result)
		baggages_.erase(it, baggages_.end());
	return result;
}

bool baggage_stock::contains(const size_t bag_num) const
{
	return std::any_of(baggages_.begin(), baggages_.end(), [&bag_num](const Baggage& in_b) { return (bag_num == in_b.flight_num); });
}

void baggage_stock::print() const
{
	if (is_empty())
		std::cout << "��������� ������� ����." << std::endl << std::endl;
	else 
	{
		std::cout << "����� �����|���� ������|����� ����������|  �������  |���-��| ��� |" << std::endl;
		std::cout << "-----------+-----------+----------------+-----------+------+-----+" << std::endl;
		std::for_each(baggages_.begin(), baggages_.end(), [](const Baggage& baggage) { write(baggage); });
		std::cout << std::endl;
	}
}


bool baggage_stock::is_empty() const
{
	return baggages_.empty();
}

size_t baggage_stock::weight() const
{
	const size_t w = std::accumulate(baggages_.begin(), baggages_.end(), 0, [&](size_t num, const Baggage& b)
		{ return num + b.weight; });
	return w;
}

size_t baggage_stock::size() const
{
	return baggages_.size();
}

void baggage_stock::clear()
{
	baggages_.clear();
}

void baggage_stock::shrink(size_t size)
{
	baggages_.resize(size);
}

baggage_stock baggage_stock::linear_search(std::function<bool(const Baggage&)> predicate) const
{
	baggage_stock result_stock;
	std::for_each(baggages_.begin(), baggages_.end(), [&](const Baggage& baggage)
		{
			if (predicate(baggage)) result_stock.add(baggage);
		});
	
	std::copy_if(baggages_.begin(), baggages_.end(), result_stock.baggages_.begin(), predicate);
	return result_stock;
}

std::istream& operator>>(std::istream& in, baggage_stock& stock)
{
	/*std::string tmp;
	getline(in, tmp);
	if (!in.eof())
	{
		std::istream_iterator<Baggage> in_iter(in);
		const std::istream_iterator<Baggage> eof_iter;
		stock.add(*in_iter);
		while (in_iter != eof_iter) {
			std::cout << "a";
			stock.add(*++in_iter);
		}
	}*/

	std::istream_iterator<Baggage> in_iter(in);
	std::istream_iterator<Baggage> eof_iter;
	std::string tmp;
	std::for_each(in_iter, eof_iter, [&](const Baggage& b) { stock.add(b); getline(in, tmp); });
	
	return in;
}


std::ostream& operator<<(std::ostream& out, const baggage_stock& stock)
{
	std::ostream_iterator<Baggage> iter(out);
	std::for_each(stock.baggages_.begin(), stock.baggages_.end(),
		[&](const Baggage& b) { *iter++ = b; out << std::endl; });
	return out;
}



