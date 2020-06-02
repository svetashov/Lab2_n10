#include "BaggageStock.h"
#include <algorithm>
#include <stdexcept>
#include <streambuf>
#include <iterator>
#include <numeric>
#include <iomanip>
#include <vector>

BaggageStock::BaggageStock()
{
	baggages_ = std::vector<Baggage>();
}

void BaggageStock::add(const Baggage& b)
{
	if (contains(b.flight_num))
		throw std::invalid_argument("Данный багаж уже добавлен.");
	baggages_.push_back(b);
}

void BaggageStock::update(const Baggage& b)
{
	const auto it = std::find_if(baggages_.begin(), baggages_.end(), [&b](const Baggage& other)
		{
			return other.flight_num == b.flight_num;
		});
	if (it == baggages_.end())
		throw std::invalid_argument("Багаж не найден в базе.");
	*it = b;
}

bool BaggageStock::remove(size_t flight_num)
{
	const auto it = std::remove_if(baggages_.begin(), baggages_.end(),
		[&flight_num](Baggage& other) { return flight_num == other.flight_num; });
	const bool result = it != baggages_.end();
	if (result)
		baggages_.erase(it, baggages_.end());
	return result;
}

bool BaggageStock::contains(const size_t bag_num) const
{
	return std::any_of(baggages_.begin(), baggages_.end(), [&bag_num](const Baggage& in_b) { return (bag_num == in_b.flight_num); });
}

void BaggageStock::print() const
{
	if (is_empty())
		std::cout << "Контейнер багажей пуст." << std::endl << std::endl;
	else 
	{
		std::cout << "Номер рейса|Дата вылета|Пункт назначения|  Фамилия  |Кол-во| Вес |" << std::endl;
		std::cout << "-----------+-----------+----------------+-----------+------+-----+" << std::endl;
		std::for_each(baggages_.begin(), baggages_.end(), [](const Baggage& baggage) { write(baggage); });
		std::cout << std::endl;
	}
}


bool BaggageStock::is_empty() const
{
	return baggages_.empty();
}

size_t BaggageStock::weight() const
{
	const size_t w = std::accumulate(baggages_.begin(), baggages_.end(), 0, [&](size_t num, const Baggage& b)
		{ return num + b.weight; });
	return w;
}

size_t BaggageStock::size() const
{
	return baggages_.size();
}

void BaggageStock::clear()
{
	baggages_.clear();
}

void BaggageStock::shrink(size_t size)
{
	baggages_.resize(size);
}

BaggageStock BaggageStock::linear_search(std::function<bool(const Baggage&)> predicate) const
{
	BaggageStock result_stock;
	std::for_each(baggages_.begin(), baggages_.end(), [&](const Baggage& baggage)
		{
			if (predicate(baggage)) result_stock.add(baggage);
		});
	
	std::copy_if(baggages_.begin(), baggages_.end(), result_stock.baggages_.begin(), predicate);
	return result_stock;
}

std::istream& operator>>(std::istream& in, BaggageStock& stock)
{
	std::istream_iterator<Baggage> in_iter(in);
	std::istream_iterator<Baggage> eof_iter;
	std::string tmp;
	std::for_each(in_iter, eof_iter, [&](const Baggage& b) { stock.add(b); getline(in, tmp); });
	return in;
}


std::ostream& operator<<(std::ostream& out, const BaggageStock& stock)
{
	std::ostream_iterator<Baggage> iter(out);
	std::for_each(stock.baggages_.begin(), stock.baggages_.end(),
		[&](const Baggage& b) { *iter++ = b; out << std::endl; });
	return out;
}



