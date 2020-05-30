#pragma once
#include "baggage.h"
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

class baggage_stock
{
	
public:
	baggage_stock();

	// Добавление нового багажа
	void add(const Baggage& b);
	
	// Изменение багажа b1 на b2
	void change(const Baggage& b1, const Baggage& b2);

	// Удаление багажа
	void remove(const Baggage& b);

	// Проверка контейнера на содержание багажа
	bool contains(const Baggage& b) const;

	// Вывод всех багажей в консоль
	void print() const;

	// Возвращает, пуст ли контейнер
	bool is_empty() const;

	// Подсчет общего веса всех багажей
	size_t weight() const;

	// Бинарный поиск в контейнере с использованием предикатов
	template <typename T>
	baggage_stock binary_search_ver1(const T& target, 
		std::function<bool(const Baggage&, const Baggage&)> less, 
		std::function<bool(const Baggage&, const T&)> less_bounds, 
		std::function<bool(const Baggage&, const T&)> more_bounds)
	{
		baggage_stock result = baggage_stock();
		baggage_stock tmp = baggage_stock();
		std::copy(baggages_.begin(), baggages_.end(), std::back_inserter(tmp.baggages_));
		std::sort(tmp.baggages_.begin(), tmp.baggages_.end(), less);

		auto low = std::lower_bound(tmp.baggages_.begin(), tmp.baggages_.end(), target,
			[&less_bounds](const Baggage& b, const T& elem) { return less_bounds(b, elem); });
		auto up = std::upper_bound(tmp.baggages_.begin(), tmp.baggages_.end(), target,
			[&more_bounds](const T& elem, const Baggage& b) { return more_bounds(b, elem); });
		
		auto begin = std::back_inserter(result.baggages_);
		std::copy(low, up, begin);

		return result;
	}

	// Бинарный поиск в контейнере с использованием предикатов
	template <typename T>
	baggage_stock binary_search(const T& target, std::function<T(const Baggage&)> value)
	{
		baggage_stock result = baggage_stock();
		baggage_stock tmp = baggage_stock();
		std::copy(baggages_.begin(), baggages_.end(), std::back_inserter(tmp.baggages_));
		std::sort(tmp.baggages_.begin(), tmp.baggages_.end(), [&value](const Baggage& b1, const Baggage& b2)
			{ return compare(value(b1), value(b2)) < 0; });

		auto low = std::lower_bound(tmp.baggages_.begin(), tmp.baggages_.end(), target,
			[&value](const Baggage& b, const T& elem) { return compare(value(b), elem) < 0; });
		auto up = std::upper_bound(tmp.baggages_.begin(), tmp.baggages_.end(), target,
			[&value](const T& elem, const Baggage& b) { return compare(elem, value(b)) < 0; });

		auto begin = std::back_inserter(result.baggages_);
		std::copy(low, up, begin);

		return result;
	}

	
	baggage_stock linear_search(std::function<bool(const Baggage&)> predicate) const;

	friend std::istream& operator>> (std::istream& in, baggage_stock& stock);

	friend std::ostream& operator<< (std::ostream& out, const baggage_stock& stock);
	
private:
	std::vector<Baggage> baggages_;
};



