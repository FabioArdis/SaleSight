#include "gnuplot-iostream.h"
#include "SalesData.hpp"

#include <map>
#include <sstream>
#include <iomanip>
#include <filesystem>

void SalesData::addRecord(const SalesRecord& record)
{
    records.push_back(record);
}

std::optional<SalesRecord> SalesData::getRecord(size_t index) const
{
    if (index < records.size())
    {
        return records[index];
    }

    return std::nullopt;
}

void SalesData::displayRecords() const
{
    std::cout << std::setw(10) << "Date" << std::setw(15) << "Product"
            << std::setw(10) << "Qty" << std::setw(10) << "Price"
            << std::setw(12) << "Total" << std::endl;

    std::cout << std::string(60, '-') << std::endl;

    for (const auto& record : records) 
    {
        record.display();
    }
}

bool SalesData::importFromCSV(const std::string &filename)
{
    std::string fname = filename + ".csv";
    if (!std::filesystem::exists(fname))
    {
        std::cerr << "File does not exist: " << fname + ".csv" << std::endl;
        return false;
    }


    std::ifstream file(fname);

    if (!file.is_open())
    {
        std::cerr << "Could not open file: " << fname << std::endl;
        return false;
    }

    std::string line;

    while (getline(file, line))
    {
        std::istringstream ss(line);

        std::string date, product;
        int quantity;
        double price;

        if (getline(ss, date, ',') &&
            getline(ss, product, ',') &&
            ss >> quantity &&
            ss.ignore() &&
            ss >> price) 
        {
            addRecord(SalesRecord(date, product, quantity, price));   
        }
    }

    file.close();

    return true;
}

bool SalesData::exportToCSV(const std::string &filename)
{
    std::string fname = filename + ".csv";

    std::ofstream file(fname);

    if(!file.is_open())
    {
        std::cerr << "Could not open file for writing: " << fname << std::endl;
        return false;
    }

    file << "date,product,quantity,price\n";

    for (const auto& record : records)
    {
        file << record.date << ','
             << record.product << ','
             << record.quantity << ','
             << record.price << '\n';
    }

    file.close();

    return true;
}

double SalesData::calculateTotalSales() const
{
    double total = 0.0;

    for (const auto& record : records)
    {
        total += (record.quantity * record.price);
    }

    return total;
}

double SalesData::calculateAverageSalesPerProduct(const std::string &product) const
{
    double total = 0.0;

    int count = 0;

    for (const auto& record : records)
    {
        if (record.product == product)
        {
            total += (record.quantity * record.price);
            count += record.quantity;
        }
    }

    return count > 0 ? total / count : 0.0;
}

std::vector<SalesRecord> SalesData::filterByDateRange(const std::string &startDate, const std::string &endDate) const
{
    std::vector<SalesRecord> filteredRecords;

    for (const auto& record : records)
    {
        if (record.date >= startDate && record.date <= endDate)
        {
            filteredRecords.push_back(record);
        }
    }

    return filteredRecords;
}

void SalesData::plotTotalSalesByProduct() const
{
    std::map<std::string, double> productSales;

    for (const auto& record : records)
    {
        productSales[record.product] += record.quantity * record.price;
    }

    std::vector<std::pair<std::string, double>> salesData;
    for (const auto& entry : productSales)
    {
        salesData.emplace_back(entry.first, entry.second);
    }

    Gnuplot gp;

    gp << "set title 'Total Sales by Product'\n";
    gp << "set xlabel 'Product'\n";
    gp << "set ylabel 'Total Sales ($)'\n";
    gp << "set style data histograms\n";
    gp << "set style fill solid 1.0 border -1\n";
    gp << "plot '-' using 2:xtic(1) title 'Sales' with histograms\n";

    gp.send1d(salesData);
}
