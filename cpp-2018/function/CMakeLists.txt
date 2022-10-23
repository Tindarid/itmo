cmake_minimum_required(VERSION 2.8)

project(function)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -D__GLIBCXX_DEBUG -Wall -Wextra")
add_executable(${PROJECT_NAME} "main.cpp" "function.h")
