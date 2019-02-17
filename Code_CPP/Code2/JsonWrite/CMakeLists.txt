cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(ProExecu JsonWrite)

project(${ProExecu})

add_definitions(-D MACRO_PREDEFINE_WRITE)

include_directories(../Third_JsonCpp/include)

set(SRCS_FILES JsonWrite/main.cpp
               JsonWrite/pch.cpp)

if(WIN32)
	set(LIB_DIR ../lib/Debug)
else()
	set(LIB_DIR ../lib)
endif()

link_directories(${LIB_DIR})

if(WIN32)
	link_libraries(Json.lib)
else()
    link_libraries(libJson.a)
endif()

add_executable(${ProExecu} ${SRCS_FILES})