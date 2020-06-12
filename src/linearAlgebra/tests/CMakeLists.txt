file(GLOB CPPFILES *.cpp)
cpp_test_program(test_${LIBRARY_NAME}
    CPPFILES
        ${CPPFILES}
    LIBRARIES
        linearAlgebra
)
