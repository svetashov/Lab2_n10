// Lab2_n10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "baggage.h"
#include "baggage_stock.h"


int main()
{
	setlocale(LC_ALL, "Russian");
    std::cout << "Hello world!\n";
	baggage_stock st = baggage_stock();

	st.add(Baggage(1242, Date(2000, 8, 15), "Москва", "Светашов", 34, 3));
	st.add(Baggage(1243, Date(2012, 9, 1), "Воронеж", "Светашов", 35, 2));
	st.add(Baggage(1244, Date(2007, 11, 29), "Москва", "Астахова", 36, 1));
	st.add(Baggage(1245, Date(2015, 9, 13), "Москва", "Астахова", 37, 3));
	st.add(Baggage(1246, Date(2016, 11, 29), "Москва", "Астахова", 38, 1));
	st.print();

	baggage_stock st2 = baggage_stock();
	baggage_stock st3 = baggage_stock();
	std::string s = "Астахова";
	
	st2 = st.linear_search([&s](const Baggage& b) {return b.surname == s; });
	/*st3 = st.binary_search<int>(1, 
		[](const Baggage& b1, const Baggage& b2) { return b1.weight < b2.weight; }, 
		[](const Baggage& b, const int str) { return b.weight < str; },
		[](const Baggage& b, const int str) { return b.weight > str; });*/
	st3 = st.binary_search<std::string>(s, [&](const Baggage& b) {return b.surname; });
	st2.print();
	st3.print();

}

