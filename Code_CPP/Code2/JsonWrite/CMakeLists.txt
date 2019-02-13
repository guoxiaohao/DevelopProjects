cmake_minimum_required(VERSION 3.1)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(ProExecu JsonWrite)

project(${ProExecu})

add_definitions(-D MACRO_PREDEFINES)

include_directories(
../include)

set(SRCS_FILES files/main.cpp
               files/pch.cpp)

set(LIB_DIR ../lib)
link_directories(${LIB_DIR})
link_libraries(libJson.a)

add_executable(${ProExecu} ${SRCS_FILES})