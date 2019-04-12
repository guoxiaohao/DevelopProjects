cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(ExeName ExeGlpkPack)
project(${ExeName})

link_directories(/usr/local/lib)
link_directories(../../../Third/lib/libJsoncpp)

include_directories(../../SDK1)
include_directories(../../../Third/include/includeJsoncpp/include)

set(SRCS src/main.cpp 
         src/glpk_cal.cpp 
		 src/result_json.cpp 
         src/pch.cpp 
         ../../SDK1/sdk_glpk_data.cpp)

if(WIN32)
else()
    link_libraries(libJson.a)
endif()
		 
add_executable(${ExeName} ${SRCS})

if(WIN32)
else()
    target_link_libraries(${ExeName} -lglpk)
endif()