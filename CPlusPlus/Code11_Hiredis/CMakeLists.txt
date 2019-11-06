cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)

set(ProjExe ExeHiredis)
project(${ProjExe})

include_directories(${CMAKE_SOURCE_DIR}/../../Third/include/)

set(LIB_DIR ${CMAKE_SOURCE_DIR}/../../Third/lib/libhiredis)

set(SRC_FILES src/main.cpp 
              src/MyRedis.cpp 
              src/pch.cpp)

add_executable(${ProjExe} ${SRC_FILES})

target_link_libraries(${ProjExe} ${LIB_DIR}/libhiredis.so.0.14)