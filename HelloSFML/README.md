# SFML Starter Project

This repo is a Visual Studio 2019 starter project using the SFML x64 C++ libraries.

- SDL library in C/C++ (GeeksforGeeks)
- SFML Graphics Library: Quick Tutorial (GeeksforGeeks)

---------


## [SFML and Visual Studio](https://www.sfml-dev.org/tutorials/2.5/start-vc.php)

In the project's properties, add:

The path to the SFML headers (`<sfml-install-path>/include`) to C/C++ > General > Additional Include Directories
The path to the SFML libraries (`<sfml-install-path>/lib`) to Linker > General > Additional Library Directories

Now link your application to the SFML libraries (.lib files) that your code will need in Linker » Input » Additional Dependencies. Add all the SFML libraries that you need such as `sfml-graphics.lib`, `sfml-window.lib` and `sfml-system.lib`.

Add the path to DLLs (`<sfml-install-path>/bin`) to `PATH` in Project Properties > Debugging > Environment

```bash
  PATH=%PATH%;%HOME%\sfml-2.5.1\bin
```

---------

