#include "SalesData.hpp"

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
