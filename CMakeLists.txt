cmake_minimum_required(VERSION 3.10)

project(SaleSight VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED COMPONENTS iostreams)
find_package(GTest REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(gnuplot-iostream)

enable_testing()

add_executable(salesight main.cpp SalesData.cpp util.cpp)
target_link_libraries(salesight Boost::iostreams)

add_executable(test_salesdata SalesDataTest.cpp SalesData.cpp)
target_link_libraries(test_salesdata Boost::iostreams GTest::gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(test_salesdata)

add_custom_target(run
    COMMAND salesight
    DEPENDS salesight
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)