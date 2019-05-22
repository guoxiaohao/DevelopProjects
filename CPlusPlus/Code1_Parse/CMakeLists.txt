cmake_minimum_required(VERSION 3.1)

<<<<<<< HEAD:CPlusPlus/Code1_Parse/CMakeLists.txt
if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)
add_subdirectory(ParseVInt)
=======
set(ExeName ExeClientSimpleProtobuf)
project(${ExeName})

set(SRCS main.cpp 
         client_use.cpp
         pch.cpp)

add_executable(${ExeName} ${SRCS})

if(WIN32)
else()
    #target_link_libraries(${ExeName} -lprotobuf)
    #target_link_libraries(${ExeName} -lpthread)
    #target_link_libraries(${ExeName} protobuf_communicate)
endif()
>>>>>>> modify in 20190522:CPlusPlus/Code2_Net/ClientSimple/CMakeLists.txt
