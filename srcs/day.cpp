module day;

import std;

std::shared_ptr<Day> get_day(int n)
{
    switch (n) {
        case 01:
            return std::make_shared<Day01>();
        case 02:
            return std::make_shared<Day02>();
        case 03:
            return std::make_shared<Day03>();
        case 04:
            return std::make_shared<Day04>();
        case 05:
            return std::make_shared<Day05>();
        case 06:
            return std::make_shared<Day06>();
        case 07:
            return std::make_shared<Day07>();
        default:
            return {};
    }
}