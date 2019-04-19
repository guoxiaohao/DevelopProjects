cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)

set(SRC_FILES src/Parase.cpp 
              src/ParaUse.cpp 
              src/pch.cpp)

add_library(ParaseCalculate STATIC ${SRC_FILES})
