#ifndef SALESIGHTEXCEPTIONS_HPP
#define SALESIGHTEXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class InvalidInputException : public std::invalid_argument
{
public:
    explicit InvalidInputException(const std::string& message)
        : std::invalid_argument(message) {}
};

class FileOperationException : public std::runtime_error
{
public:
    explicit FileOperationException(const std::string& message)
        : std::runtime_error(message) {}
};

class DateException : public std::runtime_error
{
public:
    explicit DateException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif