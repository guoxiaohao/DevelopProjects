cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)

set(ProjExe ExePool)
project(${ProjExe})

set(SRC_FILES src/main.cpp 
              src/pools_use.cpp
              src/pch.cpp)

add_executable(${ProjExe} ${SRC_FILES})

target_link_libraries(${ProjExe} -lpthread)