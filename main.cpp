#include "SalesData.hpp"
#include "SalesRecord.hpp"
#include "util.hpp"

using namespace std;

int main() 
{
	SalesData data;

	std::optional<int> choice;

	do 
	{
		cout << "\n=== SaleSight ===\n"
        	 << "1. Import Sales Data (CSV)\n"
        	 << "2. Enter Sales Data Manually\n"
        	 << "3. View Sales Summary\n"
        	 << "4. Export Sales Data (CSV)\n"
        	 << "5. Calculate Total Sales\n"
        	 << "6. Calculate Average Sales Per Product\n"
        	 << "7. Filter Sales By Date Range\n"
        	 << "8. Plot Total Sales by Product\n"
			 << "9. Exit\n";
        choice = getiInput("Enter your choice: ");

		switch (choice.value_or(-1))
		{
		case 1:
		{	
			string filename;

			cout << "Enter the CSV filename: ";
			cin >> filename;

			if (data.importFromCSV(filename))
			{
				cout << "Data imported successfully.\n";
			} else {
				cout << "Failed to import data.\n";
			}

			break;
		}

		case 2:
		{
			string product;

			auto date = getDateInput("Enter date (YYYY-MM-DD): ");
			auto quantity = getiInput("Enter quantity: ");
			auto price = getdInput("Enter price: ");

			cout << "Enter product name: ";
			cin >> product;

			if (quantity.has_value() && price.has_value() && date.has_value())
			{
				data.addRecord(SalesRecord(date.value(), product, quantity.value(), price.value()));
				cout << "Sales record added.\n";
			} else {
				cout << "Invalid input.\n";
			}

			break;
		}

		case 3:
			data.displayRecords();
			break;

		case 4:
		{
			string filename;
			cout << "Enter the filename to export to: ";
			cin >> filename;

			if (data.exportToCSV(filename))
			{
				cout << "Data exported successfully to " << filename + ".csv" << ".\n";
			} else {
				cout << "Failed to export data.\n";
			}

			break;
		}

		case 5:
		{
			double totalSales = data.calculateTotalSales();

			cout << "Total Sales: $" << fixed << setprecision(2) << totalSales << endl;

			break;
        }
        
		case 6:
		{
			string product;
			
			cout << "Enter product name: ";
			cin >> product;

			double avgSales = data.calculateAverageSalesPerProduct(product);
			
			cout << "Average Sales for " << product << ": $" << fixed << setprecision(2) << avgSales << endl;
			
			break;
        }

		case 7:
		{
			string startDate, endDate;
			
			auto start = getDateInput("Enter start date (YYYY-MM-DD): ");
			auto end = getDateInput("Enter end date (YYYY-MM-DD): ");

			if (start.has_value() && end.has_value())
			{
				auto filteredRecords = data.filterByDateRange(startDate, endDate);
				cout << "Filtered Sales Records:\n";

				for (const auto& record : filteredRecords)
				{
					cout << record.date << ", " << record.product << ", "
					 	 << record.quantity << ", " << record.price << endl;
				}
			} else {
				cout << "Invalid date input.\n";
			}

			
			break;
        }

		case 8:
			data.plotTotalSalesByProduct();
			break;

		case 9:
			cout << "Exiting...\n";
			break;

		default:
			cout << "Invalid choice. Try again.\n";
		}
	} while (choice.value() != 9);

	return 0;
}
