# Machine Problem 4

This is your final program, due at the end of the semester.  

This program in a continuation of your other programs.  

You should:

1. Read the file PIXA.DAT 

2. Perform World to Screen coordinate transformations to draw the data on the screen 

3. Allow for the following transformations given this keyboard input:

	L:  Move the object left
	R:  Move the object right
	U:  Move the object up
	D:  Move the object down

	I:  Move the object 'in'  (increase the Z)
	O:  Move the object 'out' (decrease the Z)

	X:  Rotate about the X axis
	Y:  Rotate about the Y axis
	Z:  Rotate about the Z axis

	1:  Reset to the beginning state

	Q:  Exit the program


## Libraries

- freeglut-3.0.0

- glfw-3.3.4.bin.WIN64
- glad (04/27/2021)
- glm-0.9.8.5

- SDL-2.0.5
- SDL2-ttf-2.0.15
- SDL2-image-2.0.5

- xtensor-0.23.4
- xtl-0.7.2
- OpenBLAS-0.3.13-x64


## Vectors

- Vector in C++ STL (GeeksforGeeks)
- Creation and Use of C++ Vector (BitDegree)
- vector class (Microsoft)


## References

- [3D Graphics with OpenGL By Example](https://www3.ntu.edu.sg/home/ehchua/programming/opengl/CG_Examples.html)

- [GLFW Getting Started](https://www.glfw.org/docs/latest/quick.html)

- [GLFW Basics](https://moddb.fandom.com/wiki/GLFW:Tutorials:Basics)


----------


## Installing xtensor

### From source with cmake

You can also install `xtensor` from source with cmake which requires that you have the `xtl` library installed on your system. 

On Windows platforms, from the source directory:

```bash
  mkdir build
  cd build
  cmake -G "NMake Makefiles" -DCMAKE_INSTALL_PREFIX=path_to_prefix ..
  nmake
  nmake install
```

`path_to_prefix` is the absolute path to the folder where cmake searches for dependencies and installs libraries. 

`xtensor` installation from cmake assumes this folder contains `include` and `lib` subfolders.

### xtensor version

On Windows,to find version see `xtensorConfigVersion.cmake`

