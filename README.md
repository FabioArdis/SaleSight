# SaleSight

SaleSight is a Sales Reporting Tool developed in C++17. It allows users to manage sales data by importing from CSV files or entering data manually, calculating total and average sales, filtering sales by date, and exporting reports. The project also integrates data visualization capabilities using gnuplot. Currently, the application features a text-based user interface. However, there are plans to develop a graphical user interface (GUI) in future versions for a more user-friendly experience.

## Features

- **Data Input**: Import sales data from CSV files or enter data manually.
- **Data Storage**: Store sales records using file I/O.
- **Sales Analysis**: Calculate total sales, average sales per product, and filter sales by date range.
- **Reporting**: Generate summary reports and export data to CSV.
- **Data Visualization**: Plot total sales by product using gnuplot.
- **Unit Testing**: Comprehensive unit tests using Google Test to ensure code reliability.
  
## Requirements

- C++17 compatible compiler
- CMake 3.10 or higher
- [Boost](https://www.boost.org/) (for iostreams)
- [gnuplot](http://www.gnuplot.info/) (for data visualization)
- [Google Test](https://github.com/google/googletest) (for unit testing)

## Installation

1. **Clone the repository**:
    ```bash
    git clone https://github.com/FabioArdis/SaleSight.git
    cd SaleSight
    ```
2. **Install dependencies**:
- Make sure you have Boost, gnuplot and Google Test installed. You can usually install them via your package manager or build them yourself. For example, on Arch Linux:
    ```bash
    sudo pacman -S boost gnuplot gtest
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
    make run
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

### Running Tests

To run the unit tests, you can execute:

```bash
    make test
```

You can also run a specific unit test, like the one provided in this repo:

```bash
    ./test_salesdata
```


## License
This project is licensed under the MIT License. See the [LICENSE](https://github.com/FabioArdis/SaleSight/blob/main/LICENSE) file for details.

## Acknowledgements
- [Boost](https://www.boost.org/) - C++ libraries.
- [gnuplot](http://www.gnuplot.info/) - Graph plotting utility.
- [Google Test ](https://github.com/google/googletest) - Framework for unit testing in C++.