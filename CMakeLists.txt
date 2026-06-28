cmake_minimum_required(VERSION 3.11.0)
project(maxgl VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(SOURCES
	source/maxgl.cpp
)

add_library(maxgl SHARED ${SOURCES})

target_include_directories(maxgl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(demos/)

add_subdirectory(pixel/)
