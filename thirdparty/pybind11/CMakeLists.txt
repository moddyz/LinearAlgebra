if(BUILD_PYTHON_BINDINGS)
    # Get the current source directory.
    set(PYBIND11_INCLUDE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    # Add as a library target.
    add_library(
        pybind11
        IMPORTED  # TODO: Figure out what this keyword does, precisely.
        INTERFACE # This library target does not provide source files.  (Header only!)
        GLOBAL    # Make this library target available in directories above this one.
    )

    # Any target which "links" against this library will inherit
    # PYBIND11_INCLUDE_DIR as a compilation include directory.
    target_include_directories(
        pybind11
        INTERFACE ${PYBIND11_INCLUDE_DIR}
    )
endif()
