cmake_minimum_required(VERSION 3.11)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_SOURCE_DIR}/../../Third/include/)

if(WIN32)
else()
	set(LIB_DIR ${CMAKE_SOURCE_DIR}/../../Third/lib/libBoost)
	link_directories(${LIB_DIR})
	link_libraries(libboost_system.a)
endif()

add_subdirectory(ClientSimple)
#add_subdirectory(ClientSelect)
add_subdirectory(ServerSimple)