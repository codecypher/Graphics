# Linear Algebra Starter Project

This repo is a Visual Studio 2019 starter project using the xtensor, xtensor-blas, and OpenBLAS libraries.

Moved dependencies to `%HOME%\xtensor`.


---------


## Linear Algebra Review

1. Be able to:

  - take a dot product
  - multiply 2 matrices together
  - describe the identity matrix
  - take the transpose of a matrix
  - find the inverse of a matrix
  - find the determinant of a matrix

2. Write C++ code to accomplish the above Linear Algebra functions.

Project Properties:

- C++ > General > Additional Include Directories > `%HOME%\xtensor\include;%HOME%\inc;`
- Linker > General > Additional Library Directories > `%HOME%\xtensor\lib\cmake;%HOME%\lib\x64;`
- Linker > Input > Additional Dependencies > `libopenblas.dll.a`
- Debugging > Environment > `PATH=%PATH%;%HOME%\lib\x64;`


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

Moved files to home directory:

1. Copy OpenBLAS-0.3.13-x64\bin folder to %HOME%\lib\x64
2. Copy OpenBLAS-0.3.13-x64\include folder to %HOME%\inc
3. Copy OpenBLAS-0.3.13-x64\lib folder to %HOME%\lib\x64


