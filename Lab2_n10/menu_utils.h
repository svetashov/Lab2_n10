#pragma once
#include "baggage_stock.h"
#include "config.h"

class menu
{
	baggage_stock stock;
	config conf;
	
public:
	menu(config& cfg);
	
	int menu_show();

	int menu_search_show();

	void menu();

	void menu_search(const baggage_stock& stock);

	void menu_print(const baggage_stock& stock);

	void menu_add(baggage_stock& stock);

	void menu_update(baggage_stock& stock);

	void menu_remove(baggage_stock& stock);

	void menu_clear(baggage_stock& stock);

	void menu_add_from_file(baggage_stock& stock);

	void menu_save_to_file(baggage_stock& stock);

	void menu_weight(baggage_stock& stock);
}


