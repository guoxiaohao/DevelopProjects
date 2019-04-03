cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(ExeName ExeGlpk)
project(${ExeName})

link_directories(/usr/local/lib)

include_directories(../SDK1)

set(SRCS src/main.cpp 
         src/handle_database.cpp
         src/sqlite_operator.cpp 
         src/pch.cpp 
         ../SDK1/sdk_files_csv.cpp)

add_executable(${ExeName} ${SRCS})

if(WIN32)
else()
    target_link_libraries(${ExeName} -lglpk)
    target_link_libraries(${ExeName} -lsqlite3)
endif()
