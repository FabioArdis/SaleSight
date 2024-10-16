#ifndef SALES_DATA_HPP
#define SALES_DATA_HPP

#include <vector>
#include <sqlite3.h>

#include "SalesRecord.hpp"

class SalesData
{
private:
    std::vector<SalesRecord> records;
    sqlite3* db;

public:
    SalesData();
    ~SalesData();

    void addRecord(const SalesRecord& record);
    std::optional<SalesRecord> getRecord(size_t index) const;

    bool recordExists(const std::string& date, const std::string& product) const;
    bool recordExistsDB(const std::string& date, const std::string& product) const;
    void displayRecords() const;

    bool importFromCSV(const std::string& filename);
    bool exportToCSV(const std::string& filename);

    bool importFromDatabase(const std::string& filename);
    bool exportToDatabase(const std::string& filename);

    double calculateTotalSales() const;
    double calculateAverageSalesPerProduct(const std::string& product) const;
    std::vector<SalesRecord> filterByDateRange(const std::string& startDate, const std::string& endDate) const;

    void plotTotalSalesByProduct() const;

    std::vector<SalesRecord> getRecords() const { return records; }
    void clearRecords() { records.clear(); }
};

#endif