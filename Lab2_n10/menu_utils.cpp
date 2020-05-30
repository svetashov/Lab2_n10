#include "menu_utils.h"
#include "Utils.h"

int menu_show()
{
	const int menu_size = 9;

	std::cout << std::endl;
	std::cout << "1: Посмотреть данные о багажах." << std::endl;
	std::cout << "2: Добавить багаж." << std::endl;
	std::cout << "3: Изменить багаж." << std::endl;
	std::cout << "4: Удалить багаж." << std::endl;
	std::cout << "5: Найти багажи." << std::endl;
	std::cout << "6: Очистить контейнер." << std::endl;
	std::cout << "7: Добавить данные из файла." << std::endl;
	std::cout << "8: Сохранить данные в файл." << std::endl;
	std::cout << "9: Найти общий вес багажей." << std::endl;
	std::cout << "0: Exit" << std::endl;
	const int choice = get_number(0, menu_size, "");
	std::cout << std::endl;
	return choice;
}

int menu_search_show()
{
	const int menu_size = 4;

	std::cout << std::endl;
	std::cout << "1: Найти по номеру рейса." << std::endl;
	std::cout << "2: Найти по дате вылета." << std::endl;
	std::cout << "3: Найти по пункту назначения." << std::endl;
	std::cout << "4: Найти по весу багажа." << std::endl;
	std::cout << "0: Exit" << std::endl;
	const int choice = get_number(0, menu_size, "");
	std::cout << std::endl;
	return choice;
}

int menu_select_algorithm()
{
	const int menu_size = 2;

	std::cout << std::endl;
	std::cout << "1: Бинарный поиск." << std::endl;
	std::cout << "2: Линейный поиск." << std::endl;
	const int choice = get_number(1, menu_size, "");
	std::cout << std::endl;
	return choice;
}

baggage_stock search_surname(const baggage_stock& stock, bool use_binary_search = false)
{
	const std::string surname = get_string(1, "Введите фамилию владельца багажа: ");
	if (use_binary_search)
		return stock.binary_search<std::string>(surname, [](const Baggage& b) { return b.surname; });
	
	return stock.linear_search([&surname](const Baggage& baggage) { return baggage.surname == surname; });
}

baggage_stock search_date(const baggage_stock& stock, bool use_binary_search = false)
{
	Date date = Date();
	std::cout << "Введите дату: " << std::endl;
	read(date);
	if (use_binary_search)
		return stock.binary_search<Date>(date, [](const Baggage& b) { return b.dep_date; });

	return stock.linear_search([&date](const Baggage& baggage) { return baggage.dep_date == date; });
}

baggage_stock search_destination(const baggage_stock& stock, bool use_binary_search = false)
{
	const std::string dest = get_string(1, "Введите пункт назначения: ");
	if (use_binary_search)
		return stock.binary_search<std::string>(dest, [](const Baggage& b) { return b.destination; });

	return stock.linear_search([&dest](const Baggage& baggage) { return baggage.destination == dest; });
}

baggage_stock search_weight(const baggage_stock& stock, bool use_binary_search = false)
{
	const int w = get_number(0, SIZE_MAX, "Введите вес багажа: ");
	if (use_binary_search)
		return stock.binary_search<int>(w, [](const Baggage& b) { return b.weight; });

	return stock.linear_search([&w](const Baggage& baggage) { return baggage.weight == w; });
}

void menu_search(const baggage_stock& stock)
{
	auto search_function = search_surname;
	int choice = -1;
	
	choice = menu_search_show();
	switch (choice)
	{
	case 1: search_function = search_surname;
		break;
	case 2: search_function = search_date;
		break;
	case 3: search_function = search_destination;
		break;
	case 4: search_function = search_weight;
		break;
	default: break;
	}

	const bool use_binary_search = menu_select_algorithm() == 1;
	baggage_stock result = search_function(stock, use_binary_search);

	if (result.size() > 0)
	{
		std::cout << "По данному запросу найдено " << result.size() << " багажей: " << std::endl;
		result.print();
	}
	else
		std::cout << "По данному запросу багажей не найдено." << std::endl;

	// TODO realize continue with this container.
	
}
