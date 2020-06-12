# LinearAlgebra {#mainpage}

\section LinearAlgebra_Introduction Introduction

LinearAlgebra is a C++ header-only computer graphics math library.  It has optional python bindings.

This is developed in tandem while working through MIT OpenCourseWare's 18.06.  Coding and documenting the data structures and operations aided with internalization of the concepts.

\section LinearAlgebra_Building Building

A convenience build script is provided at the root of the repository for building all targets, and optionally installing to a location: `./build.sh <OPTIONAL_INSTALL_LOCATION>`.

\subsection LinearAlgebra_Building_PythonBindings Building Python Bindings

To build python bindings for LinearAlgebra, set the cmake option `BUILD_PYTHON_BINDINGS="ON"` when configuring cmake.

\section LinearAlgebra_DeveloperNotes Developer Notes

\subsection LinearAlgebra_DeveloperNotes_SourceTree Source Tree

All of the C++ headers are organized under \p src/linearAlgebra.

Python bindings for are available under \p src/linearAlgebra/python.

Tests and benchmark code reside within the respective subdirectories.

\section LinearAlgebra_GitHubHosted GitHub Repository

The LinearAlgebra project is hosted on GitHub: https://github.com/moddyz/LinearAlgebra.

