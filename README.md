# SaleSight

SaleSight is a Sales Reporting Tool developed in C++17. It allows users to manage sales data by importing from CSV files or entering data manually, calculating total and average sales, filtering sales by date, and exporting reports. The project also integrates data visualization capabilities using gnuplot. Currently, the application features a text-based user interface. However, there are plans to develop a graphical user interface (GUI) in future versions for a more user-friendly experience.

## Features

- **Data Input**: Import sales data from CSV files or enter data manually.
- **Data Storage**: Store sales records using file I/O.
- **Sales Analysis**: Calculate total sales, average sales per product, and filter sales by date range.
- **Reporting**: Generate summary reports and export data to CSV.
- **Data Visualization**: Plot total sales by product using gnuplot.
  
## Requirements

- C++17 compatible compiler
- CMake 3.10 or higher
- [Boost](https://www.boost.org/) (for iostreams)
- [gnuplot](http://www.gnuplot.info/) (for data visualization)

## Installation

1. **Clone the repository**:
    ```bash
    git clone https://github.com/FabioArdis/SaleSight.git
    cd SaleSight
    ```
2. **Install dependencies**:
- Make sure you have Boost and gnuplot installed. You can usually install them via your package manager. For example, on Ubuntu:
    ```bash
    sudo apt-get install libboost-all-dev gnuplot
    ```
3. **Build the project**
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
4. **Run the application**
    ```bash
    ./salesight
    ```

## Usage
When you run the application, you will be presented with a menu to choose from various options such as importing data, entering sales manually, viewing summaries, and exporting data.

### Example CSV Format
When importing sales data, use the following CSV format:

```csv
date,product,quantity,price
2024-01-01,Product A,10,19.99
2024-01-02,Product B,5,9.99
```

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgements
- [Boost](https://www.boost.org/) - C++ libraries.
- [gnuplot](http://www.gnuplot.info/) - Graph plotting utility.