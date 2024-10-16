#include "gnuplot-iostream.h"
#include "SalesData.hpp"
#include "SaleSightExceptions.hpp"

#include <map>
#include <sstream>
#include <iomanip>
#include <filesystem>

SalesData::SalesData() : db(nullptr)
{
}

SalesData::~SalesData()
{
    if (db)
    {
        sqlite3_close(db);
    }
}

void SalesData::addRecord(const SalesRecord &record)
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

bool SalesData::recordExists(const std::string &date, const std::string &product) const
{
    for (const auto& record : records)
    {
        if (record.date == date && record.product == product)
        {
            return true;
        }
    }

    return false;
}

bool SalesData::recordExistsDB(const std::string &date, const std::string &product) const
{
    sqlite3_stmt* stmt;
    std::string query = "SELECT COUNT(*) FROM sales WHERE date = ? AND product = ?";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw SQLiteOperationException("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_bind_text(stmt, 1, date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, product.c_str(), -1, SQLITE_STATIC);

    int count = 0;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    return count > 0;
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
        throw FileOperationException("File does not exist: " + fname);
        return false;
    }

    std::ifstream file(fname);

    if (!file.is_open())
    {
        throw FileOperationException("Could not open file: " + fname);
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
        else 
        {
            throw FileOperationException("Invalid line format: " + line);
            return false;
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
        throw FileOperationException("Could not open file for writing: " + fname);
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

bool SalesData::importFromDatabase(const std::string &filename)
{
    std::string dbName = filename + ".db";

    if (!std::filesystem::exists(dbName))
    {
        throw SQLiteOperationException("Database does not exist: " + dbName);
        return false;
    }

    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK)
    {
        throw SQLiteOperationException("Could not open database: " + std::string(sqlite3_errmsg(db)));
        return false;
    }

    std::string query = "SELECT date, product, quantity, price FROM sales";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw SQLiteOperationException("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
        return false;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string product = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int quantity = sqlite3_column_int(stmt, 2);
        double price = sqlite3_column_double(stmt, 3);

        if (!recordExists(date, product))
        {
            addRecord(SalesRecord(date, product, quantity, price));
        } else {
            // Lo ignora
        }
    }

    sqlite3_finalize(stmt);

    return true;
}

bool SalesData::exportToDatabase(const std::string &filename)
{
    std::string dbName = filename + ".db";

    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK)
    {
        throw SQLiteOperationException("Could not open database: " + std::string(sqlite3_errmsg(db)));
        return false;
    }

    std::string createTableQuery =
        "CREATE TABLE IF NOT EXISTS sales ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "date TEXT NOT NULL, "
        "product TEXT NOT NULL, "
        "quantity INTEGER NOT NULL, "
        "price REAL NOT NULL);";
    
    if (sqlite3_exec(db, createTableQuery.c_str(), 0, 0, nullptr) != SQLITE_OK)
    {
        throw SQLiteOperationException("Failed to create table: " + std::string(sqlite3_errmsg(db)));
        return false;
    }

    sqlite3_stmt* stmt;
    std::string insertQuery = "INSERT INTO sales (date, product, quantity, price) VALUES (?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw SQLiteOperationException("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
        return false;
    }

    for (const auto& record : records)
    {
        if (!recordExistsDB(record.date, record.product))
        {
            sqlite3_bind_text(stmt, 1, record.date.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, record.product.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 3, record.quantity);
            sqlite3_bind_double(stmt, 4, record.price);

            if (sqlite3_step(stmt) != SQLITE_DONE)
            {
                throw SQLiteOperationException("Failed to insert data: " + std::string(sqlite3_errmsg(db)));
            }

            sqlite3_reset(stmt);
        }

        sqlite3_reset(stmt);
    }

    sqlite3_finalize(stmt);
    
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
