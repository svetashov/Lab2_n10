#include "date.h"
#include <stdexcept>

date::date(const size_t d, const size_t m, const size_t y) : day_(d), month_(m), year_(y)
{
    if (y < min_year)
        throw std::invalid_argument("Год не должен быть меньше минимального");

    switch (m)
    {
	    case 1:  // JANUARY
	    case 3:  // MARCH
	    case 5:  // MAY
	    case 7:  // JULY
	    case 8:  // AUGUST
	    case 10: // OCTOBER
	    case 12: // DECEMBER
	        if (!is_range(d, 1, 31))
				throw std::invalid_argument("Такой даты не существует");
	    case 2:
	        if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))
				if (!is_range(d, 1, 29))
					throw std::invalid_argument("Такой даты не существует");
			if (!is_range(d, 1, 28))
				throw std::invalid_argument("Такой даты не существует");
	    case 4:  // APRIL
	    case 6:  // JUNE
	    case 9:  // SEPTEMBER
	    case 11: // NOVEMBER
			if (!is_range(d, 1, 30))
				throw std::invalid_argument("Такой даты не существует");
	    default:
			throw std::invalid_argument("Такой даты не существует");
    }
}

size_t date::day() const
{
	return day_;
}

size_t date::month() const
{
	return month_;
}

size_t date::year() const
{
	return year_;
}

bool date::is_range(const size_t value, const size_t min, const size_t max)
{
    if (value < min) return false;
    if (value > max) return false;
    return true;
}
