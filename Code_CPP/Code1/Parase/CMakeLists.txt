cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib) 

set(SRC_FILES Parase/Parase.cpp
              Parase/ParaUse.cpp
              Parase/pch.cpp)

add_library(Parase STATIC ${SRC_FILES})
