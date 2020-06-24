# LinearAlgebra {#mainpage}

\section LinearAlgebra_Introduction Introduction

**LinearAlgebra** is general-purpose header-only linear algebra library.

This is developed in tandem while working through MIT OpenCourseWare's 18.06.  Coding and documenting the data structures and operations aided with internalization of the concepts.

\section Example Usage

Multiplication:
\code{.cpp}
using MatrixT = linear::Matrix< 3, 3 >;
constexpr MatrixT A(
    1, 0, 0,
    0, 5, 0,
    2, 3, 1
);
constexpr MatrixT B(
    1, 1, 0,
    1, 1, 1,
    0, 1, 1
);
constexpr MatrixT AB = linear::Multiply( A, B );
\endcode

Inversion:
\code{.cpp}
using MatrixT = linear::Matrix< 3, 3 >;
MatrixT invertable(
    1, 0, 0,
    0, 5, 0,
    2, 3, 1
);
MatrixT inverse;
assert( linear::Invert( invertable, inverse ) );
\endcode

Transpose:
\code{.cpp}
constexpr MatrixT matrix = linear::Matrix< 3, 2 >(
    1, 2,
    1, 1,
    2, 2
);
static_assert( linear::Transpose( matrix ) == linear::Matrix< 2, 3 >(
    1, 1, 2,
    2, 1, 2
) );
\endcode

Reduced row echelon form:
\code{.cpp}
using MatrixT = linear::Matrix< 3, 4 >;
MatrixT matrix(
    1, 2, 2, 2,
    2, 4, 6, 8,
    3, 6, 8, 10
);

assert( linear::ReducedRowEchelonForm( matrix ) == MatrixT(
    1, 2, 0, -2,
    0, 0, 1, 2,
    0, 0, 0, 0
) );
\endcode

\section LinearAlgebra_Building Building

A convenience build script is provided at the root of the repository for building all targets, and optionally installing to a location: `./build.sh <OPTIONAL_INSTALL_LOCATION>`.

\subsection LinearAlgebra_Building_PythonBindings Building Python Bindings

To build python bindings for LinearAlgebra, set the cmake option `BUILD_PYTHON_BINDINGS="ON"` when configuring cmake.

\section LinearAlgebra_DeveloperNotes Developer Notes

\subsection LinearAlgebra_DeveloperNotes_SourceTree Source Tree

The C++ headers are organized as follows:
- \p src/linear - Linear Algebra types and operations.
- \p src/linear/base - Common support utilities and implementation details.

Python bindings for are available under \p src/linear/python.

Tests and benchmark code reside within the respective subdirectories.

\subsection LinearAlgebra_DeveloperNotes_Motivation Motivation

This is developed in tandem while working through [MIT OpenCourseWare's 18.06](https://ocw.mit.edu/courses/mathematics/18-06-linear-algebra-spring-2010/) - thanks MIT and Professor Strang!  Coding and documenting the data structures and operations aided with internalization of the concepts. 

This project is also presents an opportunity to build experience with template metaprogramming.

\section LinearAlgebra_GitHubHosted GitHub Repository

The LinearAlgebra project is hosted on GitHub: https://github.com/moddyz/LinearAlgebra.

