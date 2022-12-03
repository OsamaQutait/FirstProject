cmake_minimum_required(VERSION 3.23)
project(FirstProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(FirstProject parent.cpp child.cpp header.h)
