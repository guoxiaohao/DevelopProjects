cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(ExeName ExeMain)
project(${ExeName})

include_directories(../ParseCalculate/src)

if(WIN32)
else()
    set(INCLUDELIB {PROJECT_BINARY_DIR}/ParseCalculate)
endif()
link_directories(${INCLUDELIB})

set(SRCS src/main.cpp
         src/pch.cpp)
		 
if(WIN32)
else()
    link_libraries(libParaseCalculate.a)
endif()

add_executable(${ExeName} ${SRCS})
