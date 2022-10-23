cmake_minimum_required(VERSION 2.8)

project(HUFFMAN)

include_directories(${HUFFMAN_SOURCE_DIR})

add_executable(main
               util/main.cpp
               util/compressor.cpp
               util/compressor.h
               util/decompressor.h
               util/decompressor.cpp
               util/accumulator.h
               util/accumulator.cpp
               util/file/file_reader.cpp
               util/file/file_reader.h
               util/file/file_writer.cpp
               util/file/file_writer.h
               lib/tree.cpp
               lib/tree.h
               lib/encoder.cpp
               lib/decoder.cpp
               lib/encoder.h
               lib/decoder.h
               )

add_executable(huftest
               test/huftest
               gtest/gtest-all.cc
               gtest/gtest.h
               gtest/gtest_main.cc
               lib/tree.cpp
               lib/tree.h
               lib/encoder.cpp
               lib/decoder.cpp
               lib/encoder.h
               lib/decoder.h
               )
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

target_link_libraries(main -lpthread)
target_link_libraries(huftest -lpthread)
