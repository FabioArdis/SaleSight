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
    bool exportToCSV(const std::string& filename);
    double calculateTotalSales() const;
    double calculateAverageSalesPerProduct(const std::string& product) const;
    std::vector<SalesRecord> filterByDateRange(const std::string& startDate, const std::string& endDate) const;
    void plotTotalSalesByProduct() const;
};

#endif