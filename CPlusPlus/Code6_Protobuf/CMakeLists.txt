cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(ExeName ExeProtobuf)
project(${ExeName})

#link_directories(/usr/local/lib)

set(SRCS src/main.cpp 
         src/use_for_test.cpp 
         src/server2client.pb.cc 
         src/pch.cpp)

add_executable(${ExeName} ${SRCS})

if(WIN32)
else()
    target_link_libraries(${ExeName} -lprotobuf)
    target_link_libraries(${ExeName} -lgtest)
    target_link_libraries(${ExeName} -lpthread)
endif()