// Lab2_n10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "BaggageStock.h"
#include "Menu.h"
#include <windows.h>
#include "Utils.h"
#include "config.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	Config config = Config();
	Menu menu = Menu(config);
	menu.run();
}

