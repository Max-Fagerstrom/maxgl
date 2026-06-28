cmake_minimum_required(VERSION 3.11.0)
project(backend-opengl VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 98)

find_package(opengl REQUIRED)

# GLEW
set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )
add_subdirectory(3rdparty/GLEW/build/cmake)
add_subdirectory(3rdparty/glfw)

add_executable(pixel pixel.c)
target_link_libraries(pixel PRIVATE glfw OpenGL::GL glew)
target_include_directories(pixel PRIVATE 3rdparty/GLEW/include/)


add_library(screen screen_opengl.cpp)
target_link_libraries(screen PRIVATE glfw OpenGL::GL glew)
target_include_directories(screen PRIVATE 3rdparty/GLEW/include/ ../include/)