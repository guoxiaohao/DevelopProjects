cmake_minimum_required(VERSION 3.11)

set(projectname protobuf_communicate)
set(sources server2client.pb.cc)

add_library(${projectname} STATIC ${sources})
if(WIN32)
else()
    target_link_libraries(${projectname} -lprotobuf)
    target_link_libraries(${projectname} -lpthread)
endif()