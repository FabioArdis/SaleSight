#ifndef SALES_DATA_HPP
#define SALES_DATA_HPP

#include <vector>

#include "SalesRecord.hpp"

class SalesData
{
private:
    std::vector<SalesRecord> records;

public:

    void addRecord(const SalesRecord& record);
    std::optional<SalesRecord> getRecord(size_t index) const;
    void displayRecords() const;
    bool importFromCSV(const std::string& filename);
};

#endif