cmake_minimum_required(VERSION 3.7)
project(ipomc)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        solution.cpp)

add_executable(ipomc ${SOURCE_FILES})