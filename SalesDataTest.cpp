#include "SalesData.hpp"
#include "SalesRecord.hpp"
#include "SaleSightExceptions.hpp"
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

class SalesDataTest : public ::testing::Test
{
protected:
    SalesData salesData;

    void SetUp() override
    {
        salesData.addRecord(SalesRecord("2024-01-01", "ProductA", 5, 10.0));
        salesData.addRecord(SalesRecord("2024-01-02", "ProductB", 2, 20.0));
        salesData.addRecord(SalesRecord("2024-01-02", "ProductC", 10, 5.0));
        salesData.addRecord(SalesRecord("2024-01-02", "ProductD", 15, 15.0));

        salesData.exportToDatabase("test");
    }

    void TearDown() override
    {
        std::filesystem::remove("test.db");
        std::filesystem::remove("non_existent.db");
        std::filesystem::remove("test.csv");
        std::filesystem::remove("test_unwritable/test.csv");
    }
};

TEST_F(SalesDataTest, CalculateTotalSales)
{
    double totalSales = salesData.calculateTotalSales();
    EXPECT_EQ(totalSales, (5 * 10.0) + (2 * 20.0) + (10 * 5.0) + (15 * 15.0));
}

TEST_F(SalesDataTest, AverageSalesPerProduct)
{
    double avgSalesA = salesData.calculateAverageSalesPerProduct("ProductA");
    double avgSalesB = salesData.calculateAverageSalesPerProduct("ProductB");
    double avgSalesC = salesData.calculateAverageSalesPerProduct("ProductC");
    double avgSalesD = salesData.calculateAverageSalesPerProduct("ProductD");

    EXPECT_EQ(avgSalesA, 10.0);
    EXPECT_EQ(avgSalesB, 20.0);
    EXPECT_EQ(avgSalesC, 5.0);
    EXPECT_EQ(avgSalesD, 15.0);
}

TEST_F(SalesDataTest, AddRecord)
{
    salesData.addRecord(SalesRecord("2024-01-03", "ProductC", 3, 15.0));
    double totalSales = salesData.calculateTotalSales();
    EXPECT_EQ(totalSales, 365.0 + (3 * 15.0));
}

TEST_F(SalesDataTest, FilterByDateRange)
{
    auto filteredRecords = salesData.filterByDateRange("2024-01-01", "2024-01-01");
    EXPECT_EQ(filteredRecords.size(), 1);
    EXPECT_EQ(filteredRecords[0].product, "ProductA");
}

TEST_F(SalesDataTest, ImportNonExistentFile)
{
    EXPECT_THROW(
        salesData.importFromCSV("non_existent_file"),
        FileOperationException
    );
}

TEST_F(SalesDataTest, ImportInvalidData)
{
    std::ofstream file("test.csv");
    file << "invalid_data\n";
    file.close();

    EXPECT_THROW(
        salesData.importFromCSV("test"),
        FileOperationException
    );
}

TEST_F(SalesDataTest, ExportToUnwritableLocation)
{
    std::filesystem::create_directory("test_unwritable");
    std::filesystem::permissions("test_unwritable", std::filesystem::perms::none);

    EXPECT_THROW(
        salesData.exportToCSV("test_unwritable/test"),
        FileOperationException
    );

    std::filesystem::permissions("test_unwritable", std::filesystem::perms::all);
    std::filesystem::remove("test_unwritable");
}

TEST_F(SalesDataTest, InsertAndRetrieveRecords)
{
    salesData.addRecord(SalesRecord("2024-01-03", "ProductE", 10, 5.0));

    salesData.exportToDatabase("test");

    EXPECT_EQ(salesData.getRecords().size(), 5);

    EXPECT_EQ(salesData.getRecord(4).value().date, "2024-01-03");
    EXPECT_EQ(salesData.getRecord(4).value().product, "ProductE");
    EXPECT_EQ(salesData.getRecord(4).value().quantity, 10);
    EXPECT_EQ(salesData.getRecord(4).value().price, 5.0);
}

TEST_F(SalesDataTest, HandleSQLiteOperationException)
{
    EXPECT_THROW(
        salesData.importFromDatabase("non_existent"),
        SQLiteOperationException
    );
}