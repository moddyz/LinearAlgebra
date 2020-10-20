file(GLOB CPPFILES *.cpp)
cpp_test(test_${LIBRARY_NAME}
    CPPFILES
        ${CPPFILES}
    LIBRARIES
        linear
)
