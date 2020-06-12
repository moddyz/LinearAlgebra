include(
    Private
)

# Builds a C++ python module.
#
# pybind11 and Python::Python are automatically added as library dependencies.
#
# Multi-value Arguments:
#   CPPFILES
#       C++ source files.
#   INCLUDE_PATHS
#       Include paths for compiling the source files.
#   LIBRARIES
#       Library dependencies used for linking, but also inheriting INTERFACE properties.
#   DEFINES
#       Custom preprocessor defines to set.
#
function(
    cpp_python_module
    MODULE_NAME
)
    set(options)
    set(oneValueArgs
        TYPE
    )
    set(multiValueArgs
        CPPFILES
        INCLUDE_PATHS
        LIBRARIES
        DEFINES
    )

    cmake_parse_arguments(
        args
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )

    # Add a prefix to avoid conflict(s) between C++ targets and python target names.
    # Other targets should not be linking against python plugins anyway, so it is ok
    # if the target name is obfuscated.
    set(TARGET_NAME pylib_${MODULE_NAME})

    # Add a new shared library target.
    add_library(${TARGET_NAME}
        SHARED
        ${args_CPPFILES}
    )

    # Apply common compiler properties, and include path properties.
    _set_compile_properties(${TARGET_NAME}
        INCLUDE_PATHS
            ${args_INCLUDE_PATHS}
        DEFINES
            ${args_DEFINES}
    )

    _set_link_properties(${TARGET_NAME})

    # Strip lib prefix.
    set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "")

    # Link to libraries.
    target_link_libraries(${TARGET_NAME}
        PRIVATE
            ${args_LIBRARIES}
            Python::Python
            pybind11
    )

    set_target_properties(${TARGET_NAME}
        PROPERTIES
            OUTPUT_NAME ${MODULE_NAME}
    )


    # Install the built library.
    install(
        TARGETS ${TARGET_NAME}
        LIBRARY DESTINATION pylib
        ARCHIVE DESTINATION pylib
    )

endfunction() # cpp_library

