![Build and test](https://github.com/moddyz/LinearAlgebra/workflows/Build%20and%20test/badge.svg)

# LinearAlgebra

**LinearAlgebra** is general-purpose header-only linear algebra library.

This is developed in tandem while working through [MIT OpenCourseWare's 18.06](https://ocw.mit.edu/courses/mathematics/18-06-linear-algebra-spring-2010/) - thanks MIT and Professor Strang!

## Table of Contents

- [Dependencies](#dependencies)
- [Building](#building)
- [Example Usage](#example-usage)
- [Documentation](#documentation)

### Dependencies

The following dependencies are mandatory:
- C++ compiler (C++17)
- [CMake](https://cmake.org/documentation/) (3.12 or greater)

The following dependencies are optional:
- [Doxygen](https://www.doxygen.nl/index.html) and [graphiviz](https://graphviz.org/) for documentation.

## Building

Example snippet for building this project:
```
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX="/apps/LinearAlgebra/" ..
cmake --build  . -- VERBOSE=1 -j8 all test install
```
CMake options for configuring this project:

| CMake Variable name     | Description                                                            | Default |
| ----------------------- | ---------------------------------------------------------------------- | ------- |
| `BUILD_TESTING`         | Enable automated testing.                                              | `OFF`   |
| `BUILD_DOCUMENTATION`   | Build documentation.                                                   | `OFF`   |

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
assert( linear::Inverse( invertable, inverse ) );
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

Projection:
```cpp
linear::Matrix< 3, 1 > vector(
    2,
    3,
    4
);
linear::Matrix< 3, 2 > subspace(
    1, 1,
    0, 1,
    0, 0
);
assert( linear::Projection( vector, subspace ) == linear::Matrix< 3, 1 >(
        2,
        3,
        0
    )
);
```

Orthonormalization:
```cpp
using MatrixT = linear::Matrix< 3, 3 >;
MatrixT matrix(
    1, 2, 4,
    0, 0, 5,
    0, 3, 6
);
MatrixT orthonormal = linear::Orthonormalize( matrix );
assert( orthonormal == MatrixT(
        1, 0, 0,
        0, 0, 1,
        0, 1, 0
    )
);
```

Determinant:
```cpp
linear::Matrix< 3, 3 > matrix(
    1, 2, 3,
    2, 2, 3,
    3, 3, 3
);
assert( linear::Determinant( matrix ) == 3 );
```

## Documentation

Doxygen documentation based on the latest state of master, [hosted by GitHub Pages](https://moddyz.github.io/LinearAlgebra/).
