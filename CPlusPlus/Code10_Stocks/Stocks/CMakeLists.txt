cmake_minimum_required(VERSION 3.1)

set(ExeName Exe_stocks)

set(sources
    main.cpp 
    StockSortInfo.cpp 
    pch.cpp)

link_libraries(libJson.a)

add_executable(${ExeName} ${sources})

target_link_libraries(${ExeName} -ldl)
target_link_libraries(${ExeName} -rdynamic)
target_link_libraries(${ExeName} -lpthread)