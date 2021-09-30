cmake_minimum_required(VERSION 3.20)
project(graphiobench)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cc
        graph.h
        use_graph.cc
        use_graph.h
        mmap_toker.cc
        mmap_toker.h
        fopen_fputs.cc
        fopen_fputs.h
        fstream_sstream_getline.cc
        fstream_sstream_getline.h)

add_executable(graphiobench ${SOURCE_FILES})
