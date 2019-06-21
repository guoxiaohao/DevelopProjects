cmake_minimum_required(VERSION 3.1)

set(ExeName ExeSerSync)
project(${ExeName})

set(SRC_FILES main.cpp 
              pch.cpp)

add_executable(${ExeName} ${SRC_FILES})

if(WIN32)
else()
    target_link_libraries(${ExeName} -lpthread)
endif()