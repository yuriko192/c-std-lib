cmake_minimum_required(VERSION 4.1)
project(cstdlib C)

file(GLOB_RECURSE SOURCES src/*.c src/*.h)

set(CMAKE_C_STANDARD 23)

add_executable(newproj ${SOURCES})
