cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(ProExe MainBoost)

project(${ProExe})

include_directories(../../boost_1_64_0)

if(WIN32)
	set(LIB_DIR ../../boost_1_64_0/libWinRunS)
else()
	set(LIB_DIR ../../boost_1_64_0/libLinRunS)
endif()

link_directories(${LIB_DIR})
if(WIN32)
	link_libraries(libboost_system-vc141-mt-gd-1_64.lib)
else()
	link_libraries(libboost_system.a)
endif()

set(SRC_FILES boost_use/main.cpp
			  boost_use/pch.cpp)

add_executable(${ProExe} ${SRC_FILES})

if(WIN32)
else()
    target_link_libraries(${ProExe} pthread)
endif()