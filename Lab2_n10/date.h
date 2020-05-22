#pragma once
struct date
{
	
	date(size_t d = 1, size_t m = 1, size_t y = min_year);
	size_t day() const;
	size_t month() const;
	size_t year() const;
	
private:
	size_t day_;
	size_t month_;
	size_t year_;
	static const size_t min_year = 1970;

	static bool is_range(size_t value, size_t min, size_t max);
};

