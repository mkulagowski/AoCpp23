module day;

import std;

std::shared_ptr<Day> get_day(int n)
{
    switch (n) {
        case 1:
            return std::make_shared<Day01>();
        case 2:
            return std::make_shared<Day02>();
        case 3:
            return std::make_shared<Day03>();
        case 4:
            return std::make_shared<Day04>();
        case 5:
            return std::make_shared<Day05>();
        case 6:
            return std::make_shared<Day06>();
        case 7:
            return std::make_shared<Day07>();
        case 8:
            return std::make_shared<Day08>();
        default:
            return {};
    }
}