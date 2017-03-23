cmake_minimum_required(VERSION 2.8.11)
project(ToyLidarFilters CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_subdirectory(filters)
add_subdirectory(tests)
