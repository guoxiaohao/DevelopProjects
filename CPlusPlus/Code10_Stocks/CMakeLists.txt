cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_SOURCE_DIR}/../../Third/include/includeJsoncpp/include)

link_directories(${CMAKE_SOURCE_DIR}/../../Third/lib/libJsoncpp)

add_subdirectory(Stocks)