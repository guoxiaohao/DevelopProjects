cmake_minimum_required(VERSION 3.1)

set(LibName vint)

set(sources
    ParseVint_10.cpp)

add_library(${LibName} STATIC ${sources})