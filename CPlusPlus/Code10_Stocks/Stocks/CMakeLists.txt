cmake_minimum_required(VERSION 3.1)

set(ExeName Exe_stocks)

set(sources
    main.cpp 
    LoadLibra.cpp 
    pch.cpp)

add_executable(${ExeName} ${sources})

target_link_libraries(${ExeName} -ldl)
target_link_libraries(${ExeName} -rdynamic)
target_link_libraries(${ExeName} -lpthread)