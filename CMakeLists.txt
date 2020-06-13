cmake_minimum_required(VERSION 3.17)

# Project Name
project(
    LinearAlgebra
    VERSION 0.0
    DESCRIPTION "A general-purpose header-only linear algebra library."
    LANGUAGES CXX
)

# Options
option(BUILD_DOCUMENTATION "Build doxygen documentation." ON)
option(BUILD_PYTHON_BINDINGS "Build python bindings." ON)
option(BUILD_BENCHMARKING "Build performance benchmarking." OFF)

# Debug build flags.
set(CMAKE_CXX_FLAGS_DEBUG "-DLINEAR_ALGEBRA_DEBUG")

# Cross-platform compatibility.
if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

# Discover macros.
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_SOURCE_DIR}/cmake/macros")
include(Public)
include(Python)

# Python bindings.
if(BUILD_PYTHON_BINDINGS)
    find_package(Python COMPONENTS Development Interpreter)
    message(STATUS "Found python executable: ${Python_EXECUTABLE}")
endif()

# Testing.
if(BUILD_TESTING OR BUILD_BENCHMARKING)
    enable_testing()
    list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
endif()

if(BUILD_DOCUMENTATION)
    file(
        COPY ${CMAKE_SOURCE_DIR}/README.md
        DESTINATION ${CMAKE_BINARY_DIR}
    )

    doxygen_documentation(
        doxygen_docs
        GENERATE_TAGFILE TRUE
        DOXYFILE ${CMAKE_SOURCE_DIR}/Doxyfile.in
        INPUTS
            ${CMAKE_CURRENT_SOURCE_DIR}/src/linear
            ${CMAKE_CURRENT_SOURCE_DIR}/src/linear/base
    )
endif()

# Build targets.
add_subdirectory(thirdparty)
add_subdirectory(src)
