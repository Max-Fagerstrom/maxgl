cmake_minimum_required(VERSION 3.5.0)
project(demos VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 98)

add_executable(cube cube.cpp)
target_link_libraries(cube maxgl)