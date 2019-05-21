cmake_minimum_required(VERSION 3.11)

if(WIN32)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_BUILD_TYPE Debug)

set(PROTO_DEFINE ${CMAKE_SOURCE_DIR}/proto_dir)
execute_process(COMMAND protoc --proto_path=${PROTO_DEFINE}/ --cpp_out=${PROTO_DEFINE}/ ${PROTO_DEFINE}/server2client.proto)

add_subdirectory(proto_dir)
add_subdirectory(src)