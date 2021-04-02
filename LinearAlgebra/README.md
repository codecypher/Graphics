# Linear Algebra Review

1. Be able to:

  - take a dot product
  - multiply 2 matrices together
  - describe the identity matrix
  - take the transpose of a matrix
  - find the inverse of a matrix
  - find the determinant of a matrix

2. Write C++ code to accomplish the above Linear Algebra functions.


---------


## [xtensor](https://github.com/xtensor-stack/xtensor)

[Introduction to xtensor](https://xtensor.readthedocs.io/en/latest/index.html)

[Introduction to xtensor-blas](https://xtensor-blas.readthedocs.io/en/latest/usage.html)


```bash
  # Open Developer Command Prompt for Visual Studio
  cmake -G "NMake Makefiles" -D CMAKE_INSTALL_PREFIX=C:\Users\jholmes\xtensor ..
  nmake
  nmake install

  cmake -G "NMake Makefiles" -D CMAKE_INSTALL_PREFIX=C:\Users\jholmes\xtensor -D xtl_DIR=C:\Users\jholmes\xtensor ..
  nmake
  nmake install
```


## [OpenBLAS](https://github.com/xianyi/OpenBLAS/releases/download/v0.3.13/OpenBLAS-0.3.13-x64.zip)

[How to use OpenBLAS in Microsoft Visual Studio](https://github.com/xianyi/OpenBLAS/wiki/How-to-use-OpenBLAS-in-Microsoft-Visual-Studio)

Add `%HOME\lib` to `PATH` in Project Properties > Debugging > Environment

```bash
  PATH=%PATH%;%HOME%\lib
```