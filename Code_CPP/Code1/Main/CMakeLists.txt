cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(ProExe Main)
project(${ProExe})

include_directories(../Parase/Parase)

set(SRC_FILES Main/MainPara.cpp
              Main/pch.cpp)
if(WIN32)
    set(INCLUDELIB ../lib)
else()
    set(INCLUDELIB ../lib/Debug)
endif()
link_directories(${INCLUDELIB})

if(WIN32)
    link_libraries(Parase.lib)
else()
    link_libraries(libParase.a)
endif()

add_executable(${ProExe} ${SRC_FILES})
