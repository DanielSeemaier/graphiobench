cmake_minimum_required(VERSION 3.16)
project(graphiobench)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cc
        graph.h
        use_graph.cc
        use_graph.h
        reader/mmap_toker.cc
        reader/mmap_toker.h
        reader/fstream_sstream_getline.cc
        reader/fstream_sstream_getline.h
        writer/fopen_fputs.cc
        writer/fopen_fputs.h
        writer/fopen_fprintf.cc
        writer/fopen_fprintf.h
        writer/fstream_write.cc
        writer/fstream_write.h
        writer/fstream_pipeout.cc
        writer/fstream_pipeout.h
        writer/sstream_open_write.cc
        writer/sstream_open_write.h
        writer/mybuf_open_write.cc
        writer/mybuf_open_write.h)

add_executable(graphiobench ${SOURCE_FILES})
target_include_directories(graphiobench PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
