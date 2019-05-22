cmake_minimum_required(VERSION 3.11)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_SOURCE_DIR}/../SDK1)

add_subdirectory(ClientSimple)