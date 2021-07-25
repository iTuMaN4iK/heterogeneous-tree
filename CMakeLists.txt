cmake_minimum_required(VERSION 3.19)
project(heterogeneous_tree)

set(CMAKE_CXX_STANDARD 17)

add_library(heterogeneous_tree
        STATIC
        src/node.cpp
        )

target_include_directories(heterogeneous_tree
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )


if (MSVC)
    target_compile_options(heterogeneous_tree PRIVATE
            /W4
            )
else ()
    target_compile_options(heterogeneous_tree PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif ()

if (BUILD_TESTS)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
    add_subdirectory(tests)
endif ()