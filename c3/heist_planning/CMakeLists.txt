cmake_minimum_required(VERSION 3.8)
project(heist_planning)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        solution.cpp)

add_executable(heist_planning ${SOURCE_FILES})