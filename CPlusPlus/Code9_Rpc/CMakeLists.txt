cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_SOURCE_DIR}/../../Third/include/)

set(LIB_DIR ${CMAKE_SOURCE_DIR}/../../Third/lib/libBoost)
link_directories(${LIB_DIR})
link_libraries(libboost_system.a)

add_subdirectory(client)