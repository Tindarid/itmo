cmake_minimum_required(VERSION 2.8)

project(CIRCBUFFER)

include_directories(${CIRCBUFFER_SOURCE_DIR})

add_executable(main
               main.cpp
               circular_buffer.h
               )
add_executable(testing
               testing.cpp
               tests.inl
               circular_buffer.h
               gtest/gtest.h
               gtest/gtest-all.cc
               gtest/gtest_main.cc
               counted.cpp
               counted.h
               fault_injection.cpp
               fault_injection.h
               )
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -pedantic")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

target_link_libraries(main -lpthread)
target_link_libraries(testing -lpthread)
