// Lab2_n10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Baggage.h"
#include "baggage_stock.h"

int main()
{
	setlocale(LC_ALL, "Russian");
    std::cout << "Hello world!\n";
	baggage_stock st = baggage_stock();

	st.add(Baggage());
	st.add(Baggage(1242, Date(2000, 8, 15), "Москва", "Светашов", 1234, 3));
	st.add(Baggage(1245, Date(2012, 9, 1), "Воронеж", "Светашов", 1233, 2));
	st.add(Baggage(1244, Date(2007, 11, 29), "Москва", "Астахова", 1254, 1));
	st.print();

	
	std::cout << st.weight();

	baggage_stock st2 = baggage_stock();
	baggage_stock st3 = baggage_stock();
	std::string s = "Светашов";
	
	st2 = st.linear_search([s](const Baggage& b) {return b.surname == s; });
	//st3 = st.binary_search(s, [&s](const Baggage& b, std::string s) { return b.surname < s; }, [&](const Baggage& b1, const Baggage& b2) {return b1.surname < b2.surname; });
	st2.print();
}

