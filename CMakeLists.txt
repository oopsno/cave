cmake_minimum_required(VERSION 3.8)
project(cave)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(cave main.cpp src/objects.cpp)
