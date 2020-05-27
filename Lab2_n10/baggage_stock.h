#pragma once
#include <list>
#include "Baggage.h"
#include <iostream>

class baggage_stock
{

typedef bool (*predicate)(Baggage b);
	
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

	// Поиск багажей по предикату
	baggage_stock& find(predicate pred) const;

	friend std::istream& operator>> (std::istream& in, baggage_stock& stock);

	friend std::ostream& operator<< (std::ostream& out, const baggage_stock& stock);
	
private:
	std::list<Baggage> * baggages_;
};

