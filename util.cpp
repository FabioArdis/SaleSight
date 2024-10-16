#include "util.hpp"
#include "SaleSightExceptions.hpp"
#include <limits>
#include <regex>
#include <string>

std::optional<int> getiInput(const std::string &prompt)
{
    int value;

    while (true)
    {
        try
        {
            std::cout << prompt;
            std::cin >> value;
            if (std::cin.fail())
            {
                throw InvalidInputException("Invalid input. Please enter a valid integer.");
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        catch(const InvalidInputException& e)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << e.what() << std::endl;
        }
    }
}

std::optional<double> getdInput(const std::string& prompt)
{
    double value;

    while (true)
    {
        try
        {
            std::cout << prompt;
            std::cin >> value;
            if (std::cin.fail())
            {
                throw InvalidInputException("Invalid input. Please enter a valid number.");
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        catch(const InvalidInputException& e)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << e.what() << std::endl;
        }
    }
}

std::optional<std::string> getDateInput(const std::string &prompt)
{
    std::optional<std::string> value;
    std::string input;

    while (true)
    {
        try
        {
            std::cout << prompt;
            std::cin >> input;
            
            if (!isValidDate(input))
            {
                throw DateException("Invalid date format. Please enter in YYYY-MM-DD format.");
            }

            value = input;

            return value;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
        
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
