cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(ExeName ExeServerSimple_frame)
project(${ExeName})

set(SRCS   main.cpp 
           socket_listen.cpp 
           socket_work.cpp 
           pch.cpp)

add_executable(${ExeName} ${SRCS})

if(WIN32)
else()
    #target_link_libraries(${ExeName} -lpthread)
endif()