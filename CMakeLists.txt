cmake_minimum_required(VERSION 3.16)
project(graphiobench)

set(CMAKE_CXX_STANDARD 17)

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
        writer/fopen_fwrite.cc
        writer/fopen_fwrite.h
        writer/fstream_write.cc
        writer/fstream_write.h
        writer/fstream_pipeout.cc
        writer/fstream_pipeout.h)

add_executable(graphiobench ${SOURCE_FILES})
target_include_directories(graphiobench PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})