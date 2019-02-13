cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(MainPara)

set(DIR_SRCS files/MainPara.cpp
             files/ParaUse.cpp
             files/pch.cpp)

add_executable(MainPara ${DIR_SRCS})