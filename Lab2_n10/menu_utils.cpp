#include "menu_utils.h"
#include "Utils.h"

int menu_show()
{
	try
	{
		const int menu_size = 9;

		std::cout << std::endl;
		std::cout << "1: ���������� ������ � �������." << std::endl;
		std::cout << "2: �������� �����." << std::endl;
		std::cout << "3: �������� �����." << std::endl;
		std::cout << "4: ������� �����." << std::endl;
		std::cout << "5: ����� ������." << std::endl;
		std::cout << "6: �������� ���������." << std::endl;
		std::cout << "7: �������� ������ �� �����." << std::endl;
		std::cout << "8: ��������� ������ � ����." << std::endl;
		std::cout << "9: ����� ����� ��� �������." << std::endl;
		std::cout << "0: Exit" << std::endl;
		const int choice = get_number(0, menu_size, "");
		std::cout << std::endl;
		return choice;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		return 0;
	}
}

int menu_search_show()
{
	try
	{
		const int menu_size = 4;

		std::cout << std::endl;
		std::cout << "1: ����� �� ������ �����." << std::endl;
		std::cout << "2: ����� �� ���� ������." << std::endl;
		std::cout << "3: ����� �� ������ ����������." << std::endl;
		std::cout << "4: ����� �� ���� ������." << std::endl;
		std::cout << "0: Exit" << std::endl;
		const int choice = get_number(0, menu_size, "");
		std::cout << std::endl;
		return choice;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		return 0;
	}
}

void menu()
{
	baggage_stock baggage;
	int choice = -1;
	while (choice != 0)
	{
		choice = menu_show();
		switch (choice)
		{
		case 1: menu_print(baggage);
			break;
		case 2: menu_add(baggage);
			break;
		case 3: menu_update(baggage);
			break;
		case 4: menu_remove(baggage);
			break;
		case 5: menu_search(baggage);
			break;
		case 6: menu_clear(baggage);
			break;
		case 7: menu_add_from_file(baggage);
			break;
		case 8: menu_save_to_file(baggage);
			break;
		case 9: menu_weight(baggage);
			break;
		default: break;
		}
	}
}

int menu_select_algorithm()
{
	try
	{
		const int menu_size = 2;

		std::cout << std::endl;
		std::cout << "1: �������� �����." << std::endl;
		std::cout << "2: �������� �����." << std::endl;
		const int choice = get_number(1, menu_size, "");
		std::cout << std::endl;
		return choice;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		return 0;
	}
}

baggage_stock search_surname(const baggage_stock& stock, bool use_binary_search = false)
{
	const std::string surname = get_string(1, "������� ������� ��������� ������: ");
	if (use_binary_search)
		return stock.binary_search<std::string>(surname, [](const Baggage& b) { return b.surname; });
	
	return stock.linear_search([&surname](const Baggage& baggage) { return baggage.surname == surname; });
}

baggage_stock search_date(const baggage_stock& stock, bool use_binary_search = false)
{
	Date date = Date();
	std::cout << "������� ����: " << std::endl;
	read(date);
	if (use_binary_search)
		return stock.binary_search<Date>(date, [](const Baggage& b) { return b.dep_date; });

	return stock.linear_search([&date](const Baggage& baggage) { return baggage.dep_date == date; });
}

baggage_stock search_destination(const baggage_stock& stock, bool use_binary_search = false)
{
	const std::string dest = get_string(1, "������� ����� ����������: ");
	if (use_binary_search)
		return stock.binary_search<std::string>(dest, [](const Baggage& b) { return b.destination; });

	return stock.linear_search([&dest](const Baggage& baggage) { return baggage.destination == dest; });
}

baggage_stock search_weight(const baggage_stock& stock, bool use_binary_search = false)
{
	const int w = get_number(0, SIZE_MAX, "������� ��� ������: ");
	if (use_binary_search)
		return stock.binary_search<int>(w, [](const Baggage& b) { return b.weight; });

	return stock.linear_search([&w](const Baggage& baggage) { return baggage.weight == w; });
}

void menu_search(const baggage_stock& stock)
{
	try
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
			std::cout << "�� ������� ������� ������� " << result.size() << " �������: " << std::endl;
			result.print();
		}
		else
			std::cout << "�� ������� ������� ������� �� �������." << std::endl;

		// TODO realize continue with this container.
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	
}

void menu_print(const baggage_stock& stock)
{
	try
	{
		stock.print();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	
}

void menu_add(baggage_stock& stock)
{
	try
	{
		Baggage b = Baggage();
		read(b);
		stock.add(b);
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}

void menu_update(baggage_stock& stock)
{
	try
	{
		const int flight_num = get_number(0, INT32_MAX, "������� ����� �����: ");
		if (!stock.contains(flight_num))
			std::cout << "����� �� ������ � ����." << std::endl;
		else
		{
			std::cout << "������� ����� ������ � ������: " << std::endl;
			Baggage b = Baggage();
			b.flight_num = flight_num;
			read(b.dep_date);
			b.destination = get_string(1, "������� ����� ����������");
			b.surname = get_string(1, "������� �������");
			b.baggage_num = get_number(1, INT32_MAX, "������� ���������� ������");
			b.weight = get_number(1, INT32_MAX, "������� ��� ������");
			stock.update(b);
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}

void menu_remove(baggage_stock& stock)
{
	try
	{
		const int fl = get_number(1, SIZE_MAX, "������� ����� ������");
		if (stock.remove(fl))
			std::cout << "����� � ������� ������ " << fl << " ������� �����." << std::endl;
		else
			std::cout << "����� �� ������ � ����" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}

void menu_clear(baggage_stock& stock)
{
	try
	{
		stock.clear();
		std::cout << "���� �������." << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}

std::string get_open_filepath(const std::string& filename)
{
	return ("..\\Results\\" + filename + ".txt");
}

void menu_add_from_file(baggage_stock& stock)
{
	try
	{
		const std::string filename = get_open_filepath(get_filename("������� ��� �����"));
		std::ifstream in(filename);
		if (!in.is_open())
			std::cout << "������ ��� �������� �����." << std::endl;
		else
		{
			const int size = stock.size();
			try
			{
				in >> stock;
				std::cout << "��������� " << stock.size() - size << " ����� ������." << std::endl;
			}
			catch (std::exception& e)
			{
				stock.shrink(size);
				std::cout << e.what() << std::endl;
				std::cout << "������ �� ���� ��������." << std::endl;
			}
			in.close();
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
}

void menu_save_to_file(baggage_stock& stock)
{
	try
	{
		if (stock.is_empty())
			std::cout << "���� �����." << std::endl;
		else
		{
			const std::string filename = get_open_filepath(get_filename("������� ��� �����"));
			std::ofstream out(filename);
			if (!out.is_open())
				std::cout << "������ ��� �������� �����." << std::endl;
			else
			{
				try
				{
					out << stock;
					std::cout << "������ ������� ���������." << std::endl;
				}
				catch (std::exception& e)
				{
					std::cout << "������ ��� ������ ���������� � ����." << std::endl;
					std::cout << e.what() << std::endl;
				}
				out.close();
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
}

void menu_weight(baggage_stock& stock)
{
	try
	{
		std::cout << "����� ��� ������: " <<stock.weight() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}






