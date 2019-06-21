cmake_minimum_required(VERSION 3.1)

set(ExeName ExeServerSimple)
project(${ExeName})

set(SRCS main.cpp 
         server_accept.cpp 
         server_use.cpp 
         pch.cpp)

add_executable(${ExeName} ${SRCS})

if(WIN32)
else()
    target_link_libraries(${ExeName} -lpthread)
endif()