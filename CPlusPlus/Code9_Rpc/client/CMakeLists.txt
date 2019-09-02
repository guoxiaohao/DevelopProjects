cmake_minimum_required(VERSION 3.1)

set(ExeName Exe_client)

set(sources
    main.cpp 
    pch.cpp)

add_executable(${ExeName} ${sources})