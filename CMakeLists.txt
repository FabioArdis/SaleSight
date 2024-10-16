cmake_minimum_required(VERSION 3.10)

project(SaleSight VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED COMPONENTS iostreams)

include_directories(${Boost_INCLUDE_DIRS})

include_directories(gnuplot-iostream)

add_executable(salesight main.cpp SalesData.cpp util.cpp)

target_link_libraries(salesight Boost::iostreams)
