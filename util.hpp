#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <optional>

std::optional<int> getiInput(const std::string& prompt);
std::optional<double> getdInput(const std::string& prompt);
std::optional<std::string> getDateInput (const std::string& prompt);

bool isValidDate(const std::string& date);

#endif