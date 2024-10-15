#include "SalesData.hpp"

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