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

IMPORTANT!  When handing in your program, please zip the **source code files** only.  DO NOT HAND IN EXE OR OBJ FILES!  Do not hand in 'temporary' MSVC project files.  I must be able to compile and link your project on my computer.  If I can not compile and link your program, you will receive a zero for a grade.  If I get a virus because you send me an EXE or infected file, you will receive a zero for a grade.  Please follow instructions exactly.   
ZIP up your source code files and name your zip file as:   LastnameFirstname_MP4.zip and upload here to blackboard on time.  You must upload your zip to Blackboard before I can enter a grade.


## Libraries

- freeglut-3.0.0
- glm-0.9.8.5


## Notes

I went back and implemented Matrix and Vector classes as well as elevation views. This should have been given on the assignment page. I prefer using GLM. I have an MS in Mathematics so I already know how to operate on arrays / vectors/ matrices. It would have been time better spent studying for the final exam.

- 4: elevate xy-plane (front view)
- 5: elevate yz-plane (side view)
- 6: elevate xz-plane (top view)



## Vectors

- Vector in C++ STL (GeeksforGeeks)
- Creation and Use of C++ Vector (BitDegree)
- vector class (Microsoft)


## [3D Graphics with OpenGL By Examples](https://www3.ntu.edu.sg/home/ehchua/programming/opengl/CG_Examples.html)


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


