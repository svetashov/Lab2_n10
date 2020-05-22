#pragma once
#include <list>
#include "baggage.h"

class baggage_stock
{

typedef bool (*predicate)(baggage b);
	
public:
	baggage_stock();

	// Добавление нового багажа
	void add(baggage b);
	
	// Изменение багажа b1 на b2
	void change(baggage b1, baggage b2);

	// Удаление багажа
	void remove(baggage b);

	// Вывод всех багажей в поток
	void output(std::streambuf buf) const;

	// Ввод багажей из потока
	void input(std::streambuf buf);

	// Подсчет общего веса всех багажей
	size_t weight() const;

	// Поиск багажей по предикату
	baggage_stock* find(predicate pred) const;
	
private:
	std::list<baggage> baggages;
};

