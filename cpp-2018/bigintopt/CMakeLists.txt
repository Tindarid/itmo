cmake_minimum_required(VERSION 2.8)

project(TESTBIGINTOPT)

include_directories(${TESTBIGINTOPT_SOURCE_DIR})

add_executable(big_integer_testing
               big_integer_testing.cpp
               big_integer.h
               big_integer.cpp
               myvector/myvector.h
               myvector/myvector.cpp
               gtest/gtest-all.cc
               gtest/gtest.h
               gtest/gtest_main.cc)

add_executable(main
               main.cpp
               big_integer.h
               big_integer.cpp
               myvector/myvector.h
               myvector/myvector.cpp)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

target_link_libraries(big_integer_testing -lpthread)
target_link_libraries(main -lgmp -lgmpxx -lpthread)
