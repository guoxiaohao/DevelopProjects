cmake_minimum_required(VERSION 3.1)

set(ProjExe ExeEpoll)
project(${ProjExe})

set(SRC_FILES main.cpp 
              epoll_sokcets.cpp 
              my_server_listen.cpp 
              my_connection.cpp 
              pch.cpp)

add_executable(${ProjExe} ${SRC_FILES})
target_link_libraries(${ProjExe} -lpthread)