cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

include_directories(${CMAKE_SOURCE_DIR}/../../Third/flat_hash_map-master/)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)
add_subdirectory(ParseVInt)