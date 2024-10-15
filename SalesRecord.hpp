#ifndef SALES_RECORD_HPP
#define SALES_RECORD_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <optional>
#include <iomanip>

class SalesRecord
{
public:
	std::string date;
	std::string product;
	int quantity;
	double price;
	double totalSales;

	SalesRecord(std::string d, std::string p, int q, double pr)
		: date(move(d)), product(move(p)), quantity(q), price(pr), totalSales(q * pr) {}

	void display() const 
	{
		std::cout << std::setw(10) << date << std::setw(15) << product
		     << std::setw(10) << quantity << std::setw (10) << price
		     << std::setw(12) << totalSales << std::endl;
	}

};

#endif