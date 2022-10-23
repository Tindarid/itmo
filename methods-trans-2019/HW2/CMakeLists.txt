cmake_minimum_required(VERSION 2.8)

project(PASCAL)

include_directories(${PASCAL_SOURCE_DIR})

add_executable(main main.cpp)

add_executable(test
               test.cpp
               gtest/gtest-all.cc
               gtest/gtest.h
               gtest/gtest_main.cc
               )

target_link_libraries(test -lpthread)
