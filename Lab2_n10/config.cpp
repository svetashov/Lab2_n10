#include "config.h"
#include <fstream>
#include <iostream>
#include "Utils.h"

bool Config::try_load_config()
{
	try
	{
		bool ok = true;
		std::ifstream in(CONFIG_PATH);
		ok = in.is_open();
		if (ok)
		{
			std::string tmp;
			std::getline(in, tmp);
			std::string name, value;
			ok = get_prop(tmp, name, value) && name == "default_file";
			if (ok)
			{
				default_path = value;
			}
			in.close();
		}
		return ok;
		
	}
	catch (...)
	{
		return false;
	}
	
	
}

Config::Config()
{
	if (!try_load_config())
	{
		std::cout << CONFIG_PATH << " не найден. Программа запущена со стандартными настройками." << std::endl;
		default_path = DEFAULT_PATH;
		std::ofstream out(CONFIG_PATH);
		if (!out.is_open())
			std::cout << "Ошибка при создании файла настроек." << std::endl;
		else
		{
			out << "default_file = \"" << DEFAULT_PATH << "\"" << std::endl;
		}
	}
}

std::string Config::get_default_path() const
{
	return default_path;
}
