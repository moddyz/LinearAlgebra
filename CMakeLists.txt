cmake_minimum_required(VERSION 3.12)

# Project Name
project(
    LinearAlgebra
    VERSION 0.0
    DESCRIPTION "Basic template for starting out a new CMake-based project."
    LANGUAGES CXX
)

# Set module search paths.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_CURRENT_SOURCE_DIR}/cmake
                      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tools)
# Apply options.
include(Options)

# Tools
include(Tools)

# Apply project defaults.
include(Defaults)

# Add targets.
add_subdirectory(thirdparty)
add_subdirectory(src)
