#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "Utils.h"

int32_t get_number(int32_t min, int32_t max, const std::string& message);

bool get_answer(const std::string& message);

std::string get_string(int32_t min_length, const std::string& message);

std::string get_filename(const std::string& message);

std::string get_filepath(const std::string& filename);

std::string get_value(std::string& source, const std::string& separator);
