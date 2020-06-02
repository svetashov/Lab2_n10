#pragma once
#include "BaggageStock.h"
#include "Config.h"

class Menu
{
public:
	explicit Menu(Config& cfg);

	void run();

private:

	BaggageStock stock;
	Config conf;

	static int menu_show();

	static int menu_search_show();

	void menu_search();

	void menu_print();

	void menu_add();

	void menu_update();

	void menu_remove();

	void menu_clear();

	void menu_add_from_file();

	void menu_save_to_file() const;

	void menu_weight() const;

	void menu_exit() const;

	bool try_load_from_file(std::string& file_path);
	
	bool try_save_to_file(std::string& file_path) const;
};


