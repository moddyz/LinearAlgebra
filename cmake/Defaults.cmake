# Project defaults.

if(BUILD_TESTING)
    enable_testing()
    list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
endif()

if(BUILD_DOCUMENTATION)
    doxygen_documentation(docs
        GENERATE_TAGFILE
            TRUE
        DOXYFILE
            ${PROJECT_SOURCE_DIR}/src/linear/Doxyfile.in
        INPUTS
            ${PROJECT_SOURCE_DIR}/src/linear
        DEPENDENCIES
            linear
    )
endif()
