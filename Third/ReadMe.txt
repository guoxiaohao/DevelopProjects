boost library
1 compile step:
  1.1 Execuate bootstrap generate b2 or bjam
  1.2 b2 stage --without-python --stagedir="./Libs" threading=multi link=static runtime-link=shared debug
2 directory tree:
├── include
│   └── boost
├── lib
│   └── libBoost

jsoncpp library
1 compile step:
  1.1 compile cmakelist tree:
├── CMakeLists.txt
├── include
│   └── json
│       ├── autolink.h
│       ├── config.h
│       ├── features.h
│       ├── forwards.h
│       ├── json.h
│       ├── reader.h
│       ├── value.h
│       └── writer.h
└── src
    └── lib_json
        ├── json_batchallocator.h
        ├── json_internalarray.inl
        ├── json_internalmap.inl
        ├── json_reader.cpp
        ├── json_value.cpp
        ├── json_valueiterator.inl
        ├── json_writer.cpp
        └── sconscript
2 CMakeLists.txt
cmake_minimum_required(VERSION 3.1)
if(WIN32)
else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
set(CMAKE_BUILD_TYPE Debug)
include_directories(include)
set(json_sources src/lib_json/json_batchallocator.h
                                 src/lib_json/json_internalarray.inl
                                 src/lib_json/json_internalmap.inl
                                 src/lib_json/json_reader.cpp
                                 src/lib_json/json_value.cpp
                                 src/lib_json/json_valueiterator.inl
                                 src/lib_json/json_writer.cpp)
add_library(Json STATIC ${json_sources})
3 directory tree:
├── include
│   └── includeJsoncpp
│       └── include
│           └── json
│               ├── autolink.h
│               ├── config.h
│               ├── features.h
│               ├── forwards.h
│               ├── json.h
│               ├── reader.h
│               ├── value.h
│               └── writer.h
├── lib
│   └── libJsoncpp
│       └── libJson.a

SET ENVIRONMENT:
echo "/usr/local/lib" >> /etc/ld.so.conf
ldconfig

glpk library(glpk not thread safe)
1 download glpk-XX.tar.gz
2 tar -xzvf
3 ./configure or ./configure –with-gmp
4 make
5 sudo make install

sqlite
1 tar -xzvf
2 ./configure
3 make
4 sudo make install

hiredis
1 ensure redis-server -- sudo apt-get install redis-server
2 start server -- redis-server

3 tar -xzvf
4 make
5 sudo make install
6 test success --by ./hiredis-test
7 include tree
.
├── hiredis.h
├── read.h
└── sds.h

zlib
1 tar -xzvf
2 ./configure
3 make
4 sudo make install

googletest(gtest 1.5)
1 unzip 
2 mkdir
3 cmake ..    make
4 sudo make install

protobuf
1 tar -xzvf
1.1 Maybe delete blow:
no_warning_test_CXXFLAGS = $(PTHREAD_CFLAGS) $(PTHREAD_DEF) $(ZLIB_DEF) \
                           -Wall -Wextra -Werror -Wno-unused-parameter -Og
2 ./autogen.sh generate.configure  or  .configure already existed. Then ./configure
3 make
4 make check
5 sudo make install
6 sudo ldconfig