cmake_minimum_required(VERSION 3.1)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(ExeName ExeProtobuf)
project(${ExeName})

add_definitions(-D MACRO_SAVE_FILE)
#link_directories(/usr/local/lib)

include_directories(../SDK1)

set(SRCS src/main.cpp 
         src/use_for_test.cpp 
         src/datas_send.cpp
         src/datas_recv.cpp
         src/server2client.pb.cc 
         src/pch.cpp 
        ../SDK1/sdk_files_write.cpp )

add_executable(${ExeName} ${SRCS})

if(WIN32)
else()
    target_link_libraries(${ExeName} -lprotobuf)
    target_link_libraries(${ExeName} -lpthread)
endif()