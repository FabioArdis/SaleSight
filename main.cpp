#include "SalesData.hpp"
#include "SalesRecord.hpp"

int main() 
{
	SalesData data;

	data.addRecord(SalesRecord("2024-10-14", "Item1", 10, 9.99));
	data.addRecord(SalesRecord("2024-10-10", "Item2", 5, 19.99));

	data.displayRecords();

	if (auto rec = data.getRecord(1); rec.has_value())
	{
		std::cout << "Retrieved record: ";
		rec->display();
	} else {
		std::cout << "Record not found." << std::endl;
	}
	
	return 0;
}
