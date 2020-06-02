#pragma once
#include <string>

class Config
{
	const std::string CONFIG_PATH = "config.cfg";
	const std::string DEFAULT_PATH = "/files/baggages.txt";
	
	std::string default_path;

	bool try_load_config();

public:
	Config();
	std::string get_default_path() const;
};

