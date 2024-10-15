#include "SalesData.hpp"
#include "SalesRecord.hpp"

using namespace std;

int main() 
{
	SalesData data;

	int choice;

	do 
	{
		cout << "\n=== SaleSight ===\n"
			 << "1. Import Sales Data (CSV)\n"
			 << "2. Enter Sales Data Manually\n"
			 << "3. View Sales Summary\n"
			 << "4. Export Sales Data (CSV)\n"
			 << "5. Exit\n" << std:: endl;

		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
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
			string date, product;
			int quantity;
			double price;

			cout << "Enter date (YYYY-MM-MM): ";
			cin >> date;
			cout << "Enter product name: ";
			cin >> product;
			cout << "Enter quantity: ";
			cin >> quantity;
			cout << "Enter price: ";
			cin >> price;

			data.addRecord(SalesRecord(date, product, quantity, price));
			cout << "Sales record added.\n";

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
			cout << "Exiting...\n";
			break;

		default:
			cout << "Invalid choice. Try again.\n";
		}
	} while (choice != 5);

	return 0;
}
