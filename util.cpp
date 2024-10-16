#include "util.hpp"
#include <limits>
#include <regex>
#include <string>

std::optional<int> getiInput(const std::string &prompt)
{
    int value;

    while (true)
    {
        std::cout << prompt;        
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a valid integer.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

std::optional<double> getdInput(const std::string& prompt)
{
    double value;

    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a valid number.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

std::optional<std::string> getDateInput(const std::string &prompt)
{
    std::optional<std::string> value;
    std::string input;

    std::cout << prompt;
    std::cin >> input;

    while (!isValidDate(input))
    {
        std::cout << "Invalid date format. Please enter in YYYY-MM-DD format.\n";

        std::cout << prompt;
        std::cin >> input;
    }

    value = input;
    return value;
}

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(const std::string &date)
{
    std::regex datePattern(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$)");
    if (!std::regex_match(date, datePattern))
    {
        return false;
    }

    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && isLeapYear(year))
    {
        daysInMonth[1] = 29;
    }

    if (day > daysInMonth[month - 1])
    {
        return false;
    }

    return true;
}
