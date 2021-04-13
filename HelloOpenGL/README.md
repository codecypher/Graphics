# OpenGL Starter Project

This repo is a Visual Studio 2019 starter project using OpenGL libraries (GL/GLU/GLUT) including glutdlls37beta.

All the header, DLL, and lib files are local to the project.

## freeglut (Prepackaged Releases)

[freeglut](http://freeglut.sourceforge.net/index.php#download)

The freeglut project does not support packaged versions of freeglut excepting, of course, the tarballs distributed here. However, various members of the community have put time and effort into providing source or binary rollups and we thank them for their efforts.

Here is the source used by this repo:

[Martin Payne's Windows binaries (MSVC and MinGW)](https://www.transmissionzero.co.uk/software/freeglut-devel/)

1. Copy freeglut\bin folder to `%HOME%\dll\x86` and  `%HOME%\dll\x64`
2. Copy freeglut\include folder to `%HOME%\inc`
3. Copy freegult\lib folder to `%HOME%\lib\x86` and `%HOME%\lib\x64`


----------


## Visual Studio Setup

- Game development with C++ workload
- Windows 10 SDK (10.0.19041.0)

----------


## Configure Visual Studio Locally (recommended)

Project Properties:

- C++ > General > Additional Include Directories > %HOME%\inc
- Linker > General > Additional Library Directories > %HOME%\lib\x64;%HOME%\lib
- Linker > Input > Additional Dependencies > freeglut.lib
- Debugging > Environment > PATH=%PATH%;%HOME%\bin\x64;%HOME%\bin


----------


## Configure Visual Studio Locally (standalone)

Project Properties:

- Debugging > Environment > PATH=%PATH%;$(ProjectDir)lib
- VC++ Directories > Include Directories > $(ProjectDir)inc
- VC++ Directories > Library Directories > $(ProjectDir)lib


----------


## Configure Visual Studio Globally

The following is only necessary if you want to configure Visual Studio to use the files with other new projects (probably best not to do that for this course).

Copy files to the following locations (if not already present):

- `glut.h` to `C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\VS\include\gl`
- `glut32.lib` to `C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\VS\lib\x86`
- `glut.dll` and `glut32.dll` to `C:\Windows\SysWOW64`
- `glut32.dll` to `C:\Windows\System32`


Add `%HOME%\lib` to `PATH` in Project Properties > Debugging > Environment

```bash
  PATH=%PATH%;%HOME%\lib
```

----------

## [How to setup OpenGL with Visual Studio 2019 on Windows 10?](https://www.geeksforgeeks.org/how-to-setup-opengl-with-visual-studio-2019-on-windows-10/)

Now download GLUT header file, the .LIB, and .DLL files all pre-compiled for Intel platforms: [glutdlls37beta.zip](https://www.opengl.org/resources/libraries/glut/glutdlls37beta.zip)

----------

## [Programming OpenGL in C/C++](https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html)

We need the following sets of libraries in programming OpenGL:

1. **Core OpenGL (GL):** consists of hundreds of functions, which begin with a prefix "gl" (e.g., glColor, glVertex, glTranslate, glRotate). The Core OpenGL models an object via a set of geometric primitives, such as point, line, and polygon.

2.**OpenGL Utility Library (GLU):** built on-top of the core OpenGL to provide important utilities and more building models (such as qradric surfaces). GLU functions start with a prefix "glu" (e.g., gluLookAt, gluPerspective)

3. **OpenGL Utilities Toolkit (GLUT):** provides support to interact with the Operating System (such as creating a window, handling key and mouse inputs); and more building models (such as sphere and torus). GLUT functions start with a prefix of "glut" (e.g., glutCreatewindow, glutMouseFunc).

GLUT is designed for constructing small to medium sized OpenGL programs. While GLUT is well-suited to learning OpenGL and developing simple OpenGL applications, GLUT is not a full-featured toolkit so large applications requiring sophisticated user interfaces are better off using native window system toolkits. GLUT is simple, easy, and small."

Alternative of GLUT includes SDL, ....

4. OpenGL Extension Wrangler Library (GLEW): [GLEW](http://glew.sourceforge.net/) is a cross-platform open-source C/C++ extension loading library. GLEW provides efficient run-time mechanisms for determining which OpenGL extensions are supported on the target platform.

----------

##  Installing VC++, OpenGL, GLU and GLUT

1. Visual C++: Read "How to install Visual C++ Express". VC++ would be installed in "C:\Program Files\Microsoft Visual Studio 10.0\VC", with headers in sub-directory "include" and libraries in "lib".

2. Windows SDK which includes OpenGL and GLU (OpenGL Utility). The Visual C++ 2010 Express bundles the Microsoft Windows SDK, which would be installed in "C:\Program Files\Microsoft SDKs\Windows\v7.0A". (Otherwise, you need to download and install the Windows SDK separately).

**The followings are used from the Windows SDK:**

- gl.h, glu.h: header for OpenGL and GLU in directory `C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\um\gl`.

- opengl32.lib, glu32.lib: libraries for OpenGL and GLU in directory `C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x86`.

- opengl32.dll, glu32.dll: dynamic link libraries for OpenGL and GLU in directory `C:\Windows\System32`. This directory is to be included in `PATH` environment variable.

If you use the VC++ IDE, the include-path and lib-path would have been set correctly. If you use the CMD shell, you need to run the batch file "vcvarsall.bat" (in "C:\Program Files\Microsoft Visual Studio 10.0\VC\bin"), or "vcvars32.bat" in the earlier version, to set the environment variables.

3. GLUT (OpenGL Utility Toolkit): Download Nate Robin's original Win32 port of [GLUT](http://www.xmission.com/~nate/glut.html) or [freeglut](http://freeglut.sourceforge.net). 

These files should be included in the project, but you can also copy the following files from the following locations:

- `glut.h` in `C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\um`
- `glut32.lib` in `C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x86`

----------


