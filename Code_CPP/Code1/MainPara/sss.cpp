#include "pch.h"

#include <math.h>

int main(int argc, char** argv)
{
    double doubleVal1, doubleVal2;
    doubleVal1 = 100.0;
    doubleVal2 = 144.0;

    std::cout <<  sqrt(doubleVal1) << std::endl;
    std::cout <<  sqrt(doubleVal2) << std::endl;

    system("pause");

    return 0;
}


cmake_minimum_required(VERSION 3.1)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(Code0)

set(SRCS_FILES Code0/main.cpp
               Code0/pch.cpp)

link_libraries(m)

add_executable(Code0 ${SRCS_FILES})