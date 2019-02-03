cmake_minimum_required(VERSION 3.8)
project(goalwall)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        solution.cpp)

add_executable(goalwall ${SOURCE_FILES})