cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(ExeName ExeCli)
project(${ExeName})

include_directories(../../../Third/include/)

if(WIN32)
else()
	set(LIB_DIR ../../../Third/lib/libBoost)
endif()

link_directories(${LIB_DIR})
if(WIN32)
else()
	link_libraries(libboost_system.a)
endif()

set(SRCS src/main.cpp
         src/ClientSync.cpp
         src/ClientSyncBoost.cpp
         src/pch.cpp)

add_executable(${ExeName} ${SRCS})

if(WIN32)
else()
    target_link_libraries(${ExeName} pthread)
endif()
