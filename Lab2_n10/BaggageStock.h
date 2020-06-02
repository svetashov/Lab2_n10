#pragma once
#include "Baggage.h"
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

class BaggageStock
{
	
public:
	BaggageStock();

	// Добавление нового багажа
	void add(const Baggage& b);
	
	// Изменение багажа b1 на b2
	void update(const Baggage& b);

	// Удаление багажа
	bool remove(size_t flight_num);

	// Проверка контейнера на содержание багажа
	bool contains(const size_t bag_num) const;

	// Вывод всех багажей в консоль
	void print() const;

	// Возвращает, пуст ли контейнер
	bool is_empty() const;

	// Подсчет общего веса всех багажей
	size_t weight() const;

	// Количество багажей в контейнере
	size_t size() const;

	void clear();

	void shrink(size_t size);

	// Бинарный поиск в контейнере с использованием предикатов
	template <typename T>
	BaggageStock binary_search_ver1(const T& target, 
		std::function<bool(const Baggage&, const Baggage&)> less, 
		std::function<bool(const Baggage&, const T&)> less_bounds, 
		std::function<bool(const Baggage&, const T&)> more_bounds) const
	{
		BaggageStock result = BaggageStock();
		BaggageStock tmp = BaggageStock();
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
	BaggageStock binary_search(const T& target, std::function<T(const Baggage&)> value) const
	{
		BaggageStock result = BaggageStock();
		BaggageStock tmp = BaggageStock();
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

	
	BaggageStock linear_search(std::function<bool(const Baggage&)> predicate) const;

	friend std::istream& operator>> (std::istream& in, BaggageStock& stock);

	friend std::ostream& operator<< (std::ostream& out, const BaggageStock& stock);
	
private:
	std::vector<Baggage> baggages_;
};



