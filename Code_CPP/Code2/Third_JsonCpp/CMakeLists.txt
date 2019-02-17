cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib) 

include_directories(include)

set(json_sources src/lib_json/json_batchallocator.h
				 src/lib_json/json_internalarray.inl
				 src/lib_json/json_internalmap.inl
				 src/lib_json/json_reader.cpp
				 src/lib_json/json_value.cpp
				 src/lib_json/json_valueiterator.inl
				 src/lib_json/json_writer.cpp)

add_library(Json STATIC ${json_sources})