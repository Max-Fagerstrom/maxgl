cmake_minimum_required(VERSION 3.11.0)
project(demos VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 98)

add_executable(cube cube.cpp)
target_link_libraries(cube maxgl)

# Automatically copy all linked runtime DLLs to the executable directory
if(WIN32)
    add_custom_command(TARGET cube POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:cube>
            $<TARGET_FILE_DIR:cube>
        COMMAND_EXPAND_LISTS
    )
endif()