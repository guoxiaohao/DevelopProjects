cmake_minimum_required(VERSION 3.1)

set(ExeName ExeParse)

include_directories(${CMAKE_SOURCE_DIR})

set(sources
    main.cpp 
    pch.cpp)

add_executable(${ExeName} ${sources})
target_link_libraries(${ExeName} vint)