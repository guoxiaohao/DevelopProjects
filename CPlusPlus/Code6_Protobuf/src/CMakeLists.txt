cmake_minimum_required(VERSION 3.1)

set(ExeName ExeProtobuf)
project(${ExeName})

add_definitions(-D MACRO_SAVE_FILE)

#link_directories(/usr/local/lib)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/../SDK1)

set(SRCS main.cpp 
         use_for_test.cpp 
         datas_send.cpp
         datas_recv.cpp
         pch.cpp 
         ${CMAKE_SOURCE_DIR}/../SDK1/sdk_files_write.cpp )

add_executable(${ExeName} ${SRCS})

if(WIN32)
else()
    target_link_libraries(${ExeName} -lprotobuf)
    target_link_libraries(${ExeName} -lpthread)
    target_link_libraries(${ExeName} protobuf_communicate)
endif()