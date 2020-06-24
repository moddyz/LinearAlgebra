# LinearAlgebra

**LinearAlgebra** is general-purpose header-only linear algebra library.

## Example Usage

Multiplication:
```cpp
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
```

Inversion:
```cpp
using MatrixT = linear::Matrix< 3, 3 >;
MatrixT invertable(
    1, 0, 0,
    0, 5, 0,
    2, 3, 1
);
MatrixT inverse;
assert( linear::Invert( invertable, inverse ) );
```

Transpose:
```cpp
constexpr MatrixT matrix = linear::Matrix< 3, 2 >(
    1, 2,
    1, 1,
    2, 2
);
static_assert( linear::Transpose( matrix ) == linear::Matrix< 2, 3 >(
    1, 1, 2,
    2, 1, 2
) );
```

Reduced row echelon form:
```cpp
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
```

## Building

A convenience build script is also provided, for building all targets, and optionally installing to a location:
```
./build.sh <OPTIONAL_INSTALL_LOCATION>
```
## Requirements

- `>= CMake-3.17`
- `C++17`

## Motivation

This is developed in tandem while working through [MIT OpenCourseWare's 18.06](https://ocw.mit.edu/courses/mathematics/18-06-linear-algebra-spring-2010/) - thanks MIT and Professor Strang!  Coding and documenting the data structures and operations aided with internalization of the concepts. 

This project is also presents an opportunity to build experience with template metaprogramming.

## Documentation

Doxygen documentation based on the latest state of master, [hosted by GitHub Pages](https://moddyz.github.io/LinearAlgebra/).

