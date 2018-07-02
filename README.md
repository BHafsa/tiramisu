[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE)

## Overview

Tiramisu is a compiler for expressing fast, portable and composable data parallel computations.  It provides a simple C++ API for expressing algorithms (`Tiramisu expressions`) and how these algorithms should be optimized by the compiler.  Tiramisu can be used in areas such as linear and tensor algebra, deep learning, image processing, stencil computations and machine learning.

The Tiramisu compiler is based on the polyhedral model thus it can express a large set of loop optimizations and data layout transformations.  Currently it targets (1) multicore X86 CPUs, (2) Nvidia GPUs, (3) Xilinx FPGAs (Vivado HLS) and (4) distributed machines (using MPI).  It is designed to enable easy integration of code generators for new architectures.

### Example

The user can write `Tiramisu expressions` within a C++ code as follows.

```cpp
// C++ code with a Tiramisu expression.
#include "tiramisu.h"

void foo(int N, int array_a[N], int array_b[N], int array_c[N])
{

    tiramisu::init();

    // Declare an iterator and inputs
    tiramisu::iter i, j;
    tiramisu::in A(i,j), B(i,j);

    // Declare the Tiramisu expression (algorithm)
    tiramisu::comp C(i,j) = A(i,j) + B(i,j);
    
    // Specify optimizations
    C.parallelize(i).vectorize(j, 4);

    // Realize, compile and run the expression
    C.realize(tiramisu::int32_t, {N});
    C.compile({(A, array_a), (B, array_b), (C, array_c)});
    C.run();
}
```

## Building Tiramisu

This section provides a short description of how to build Tiramisu.  A more detailed description is provided in [INSTALL](INSTALL.md).  The installation instructions below have been tested on Linux Ubuntu (14.04) and MacOS (10.12) but should work on other Linux and MacOS versions.

#### Prerequisites
###### Required
1) [CMake](https://cmake.org/): version 3.5 or greater.

2) [Autoconf](https://www.gnu.org/software/autoconf/) and [libtool](https://www.gnu.org/software/libtool/).
  
###### Optional
1) [OpenMPI](https://www.open-mpi.org/) and [OpenSSh](https://www.openssh.com/): if you want to generate and run distributed code (MPI).
2) [CUDA Toolkit](https://developer.nvidia.com/cuda-toolkit): if you want to generate and run CUDA code.


#### Building
1) Get Tiramisu

        git clone https://github.com/Tiramisu-Compiler/tiramisu.git
        cd tiramisu

2) Get and install Tiramisu submodules (ISL, LLVM and Halide).  This step may take between few minutes to few hours (downloading and compiling LLVM is time consuming).

        ./utils/scripts/install_submodules.sh <TIRAMISU_ROOT_DIR>

3) Optional: configure the tiramisu build by editing `configure.cmake`.  Needed only if you want to generate MPI or GPU code, or if you want to run the BLAS benchmarks.  A description of what each variable is and how it should be set is provided in comments in `configure.cmake`.

    - To use the GPU backend, set `USE_GPU` to `true`.  If the CUDA library is not found automatically while building Tiramisu, the user will be prompt to provide the path to the CUDA library.
    - To use the distributed backend, set `USE_MPI` to `true`.  If the MPI library is not found automatically, set the following variables: MPI_INCLUDE_DIR, MPI_LIB_DIR, and MPI_LIB_FLAGS.

4) Build the main Tiramisu library

        mkdir build
        cd build
        cmake ..
        make -j tiramisu


## Getting Started
- Build [Tiramisu](https://github.com/Tiramisu-Compiler/tiramisu/).
- Read the [Tutorials](https://github.com/Tiramisu-Compiler/tiramisu/blob/master/tutorials/README.md).
- Read the [Tiramisu Paper](https://arxiv.org/abs/1804.10694).
- Subscribe to Tiramisu [mailing list](https://lists.csail.mit.edu/mailman/listinfo/tiramisu).
- Read the compiler [internal documentation](https://tiramisu-compiler.github.io/doc/) (if you want to contribute to the compiler).


## Run Tests

To run all the tests, assuming you are in the build/ directory

    make test

or

    ctest
    
To run only one test (test_01 for example)

    ctest -R 01

This will compile and run the code generator and then the wrapper.

To view the output of a test pass the `--verbose` option to `ctest`.
