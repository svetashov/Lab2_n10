#pragma once
#include <list>
#include "Baggage.h"
#include <iostream>
#include <functional>

class baggage_stock
{
	
public:
	baggage_stock();

	// Добавление нового багажа
	void add(const Baggage& b) const;
	
	// Изменение багажа b1 на b2
	void change(const Baggage& b1, const Baggage& b2) const;

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

	template <typename T>
	baggage_stock binary_search(const T& target, bool less(const Baggage& baggage, const T& elem), bool less_binary(const Baggage& baggage1, const Baggage& baggage2)) const;
	baggage_stock linear_search(std::function<bool(const Baggage&)> predicate) const;

	friend std::istream& operator>> (std::istream& in, baggage_stock& stock);

	friend std::ostream& operator<< (std::ostream& out, const baggage_stock& stock);
	
private:
	std::list<Baggage> * baggages_;
};

