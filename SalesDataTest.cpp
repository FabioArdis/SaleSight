#include "SalesData.hpp"
#include "SalesRecord.hpp"
#include <gtest/gtest.h>

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
    }

    void TearDown() override
    {

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