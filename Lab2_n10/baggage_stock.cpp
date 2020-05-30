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
	if (contains(b))
		throw new std::invalid_argument("Данный багаж уже добавлен.");
	baggages_.push_back(b);
}

void baggage_stock::change(const Baggage& b1, const Baggage& b2)
{	
	for (auto it = baggages_.begin(); it != baggages_.end(); ++it) {
		if (*it == b1) {
			*it = b2;
			return;
		}
	}
	throw std::invalid_argument("Багажа, который требуется изменить, не существует.");
}

void baggage_stock::remove(const Baggage& b)
{
	baggages_.erase(std::remove(baggages_.begin(), baggages_.end(), b), baggages_.end());
}

bool baggage_stock::contains(const Baggage& b) const
{
	return std::any_of(baggages_.begin(), baggages_.end(), [&b](const Baggage& in_b) { return (b == in_b); });
}

void baggage_stock::print() const
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
	std::istream_iterator<Baggage> in_iter(in);
	std::istream_iterator<Baggage> eof_iter;
	std::for_each(in_iter, eof_iter, [&stock](const Baggage& b) { stock.add(b); });
	return in;
}


std::ostream& operator<<(std::ostream& out, const baggage_stock& stock)
{
	std::ostream_iterator<Baggage> iter(out);
	std::copy(stock.baggages_.cbegin(), stock.baggages_.cend(), iter);
	return out;
}



