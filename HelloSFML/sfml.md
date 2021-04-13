# [SFML Tutorial](https://www.sfml-dev.org/download/sfml/2.5.1/)

[SFML Graphics Library: Quick Tutorial](https://www.geeksforgeeks.org/sfml-graphics-library-quick-tutorial/)

## System Module

### Handling time

Unlike many other libraries where time is a uint32 number of milliseconds, or a float number of seconds, SFML doesn't impose any specific unit or type for time values. Instead it leaves this choice to the user through a flexible class: sf::Time. All SFML classes and functions that manipulate time values use this class.

sf::Time represents a time period (in other words, the time that elapses between two events). It is not a date-time class which would represent the current year/month/day/hour/minute/second as a timestamp, it's just a value that represents a certain amount of time, and how to interpret it depends on the context where it is used.

- Converting time
- Playing with time values
- Measuring time

### Threads

#### What is a thread?

A thread is basically a sequence of instructions that run in parallel to other threads. Every program is made of at least one thread: the main one, which runs your main() function. Programs that only use the main thread are single-threaded, if you add one or more threads they become multi-threaded.

So, in short, threads are a way to do multiple things at the same time. This can be useful, for example, to display an animation and reacting to user input while loading images or sounds. Threads are also widely used in network programming, to wait for data to be received while continuing to update and draw the application.

#### SFML threads or std::thread?

In its newest version (2011), the C++ standard library provides a set of classes for threading. At the time SFML was written, the C++11 standard was not written and there was no standard way of creating threads. When SFML 2.0 was released, there were still a lot of compilers that did not support the new standard.

If you work with compilers that support the new standard and its `<thread>` header, you can forget about the SFML thread classes and use it instead -- it will be much better.

### User data streams

SFML has several resource classes: images, fonts, sounds, etc. In most programs, these resources will be loaded from files with the help of their `loadFromFile` function. In a few situations, resources will be packed directly into the executable or in a big data file and loaded from memory with `loadFromMemory`. These functions cover almost all the possible use cases -- but not all.

Sometimes you want to load files from unusual places such as a compressed/encrypted archive or a remote network location for example. For these special situations, SFML provides a third loading function: `loadFromStream`. This function reads data using an abstract sf::InputStream interface, which allows you to provide your own implementation of a stream class that works with SFML.

In this tutorial you will learn how to write and use your own derived input stream.

#### And standard streams?

Like many other languages, C++ already has a class for input data streams: `std::istream`. In fact it has two: `std::istream` is only the front-end, the abstract interface to the custom data is `std::streambuf`.

Unfortunately, these classes are not very user friendly and can become very complicated if you want to implement non-trivial stuff. The` Boost.Iostreams` library tries to provide a simpler interface to standard streams but Boost is a big dependency and SFML cannot depend on it.

That is why SFML provides its own stream interface which is hopefully a lot more simple and fast.


----------


## Window Module

### Opening and managing a SFML window

This tutorial only explains how to open and manage a window. Drawing stuff is beyond the scope of the `sfml-window` module: it is handled by the `sfml-graphics` module. However, the window management remains exactly the same so reading this tutorial is important in any case.

- Opening a window
- Bringing the window to life
- Playing with the window
- Controlling the framerate

### Things to know about windows

Here is a brief list of what you can and cannot do with SFML windows.

- You can create multiple windows

  SFML allows you to create multiple windows and to handle them either all in the main thread or each one in its own thread. In this case, do not forget to have an event loop for each window.

- Multiple monitors are not correctly supported yet

  SFML does not explicitly manage multiple monitors. As a consequence, you will not be able to choose which monitor a window appears on and you will not be able to create more than one fullscreen window. This should be improved in a future version.

- Events must be polled in the window's thread

  This is an important limitation of most operating systems: the event loop (more precisely, the `pollEvent` or `waitEvent` function) must be called in the same thread that created the window. This means that if you want to create a dedicated thread for event handling, you will have to make sure that the window is created in this thread too. If you really want to split things between threads, it is more convenient to keep event handling in the main thread and move the rest (rendering, physics, logic, ...) to a separate thread instead. This configuration will also be compatible with the other limitation described below.

- On macOS, windows and events must be managed in the main thread

  macOS just will not agree if you try to create a window or handle events in a thread other than the main one.

- On Windows, a window which is bigger than the desktop will not behave correctly

  For some reason, Windows does not like windows that are bigger than the desktop. This includes windows created with `VideoMode::getDesktopMode()`: with the window decorations (borders and titlebar) added, you end up with a window that is slightly bigger than the desktop.

### Events explained

This tutorial is a detailed list of window events. It describes them and shows how to (and how not to) use them.

#### The sf::Event type

Before dealing with events, it is important to understand the `sf::Event` type and how to correctly use it. `sf::Event` is a _union_ which means that only one of its members is valid at a time (remember your C++ lesson: all the members of a union share the same memory space). The valid member is the one that matches the event type such as `event.key` for a `KeyPressed` event. 

Trying to read any other member will result in an undefined behavior (most likely: random or invalid values). It it important to never try to use an event member that does not match its type.

`sf::Event` instances are filled by the `pollEvent` (or `waitEvent`) function of the `sf::Window` class. Only these two functions can produce valid events, any attempt to use an `sf::Event` which was not returned by successful call to `pollEvent` or `waitEvent` will result in the same undefined behavior that was mentioned above.

#### The Closed event

The `sf::Event::Closed `event is triggered when the user wants to close the window through any of the possible methods the window manager provides ("close" button, keyboard shortcut, etc.). This event only represents a close request, the window is not yet closed when the event is received.

Typical code will call `window.close()` in reaction to this event to actually close the window. However, you may also want to do something else first such as saving the current application state or asking the user what to do. If you do not do anything, the window remains open.

There is no member associated with this event in the `sf::Event` union.

```cpp
    if (event.type == sf::Event::Closed)
        window.close();
```

#### The Resized event

The `sf::Event::Resized` event is triggered when the window is resized, either through user action or programmatically by calling `window.setSize`.

You can use this event to adjust the rendering settings: the viewport if you use `OpenGL` directly or the current view if you use `sfml-graphics`.

The member associated with this event is` event.size` which contains the new size of the window.

```cpp
    if (event.type == sf::Event::Resized) {
        std::cout << "new width: " << event.size.width << std::endl;
        std::cout << "new height: " << event.size.height << std::endl;
    }
```

#### The LostFocus and GainedFocus events

The `sf::Event::LostFocus` and `sf::Event::GainedFocus` events are triggered when the window loses/gains focus which happens when the user switches the currently active window. When the window is out of focus, it does not receive keyboard events.

This event can be used such as if you want to pause your game when the window is inactive.

There is no member associated with these events in the `sf::Event` union.

```cpp
    if (event.type == sf::Event::LostFocus)
        myGame.pause();

    if (event.type == sf::Event::GainedFocus)
        myGame.resume();
```

#### The TextEntered event

The `sf::Event::TextEntered` event is triggered when a character is typed. This should not be confused with the `KeyPressed` event: `TextEntered` interprets the user input and produces the appropriate printable character. 

For example, pressing '^' then 'e' on a French keyboard will produce two `KeyPressed` events but a single `TextEntered` event containing the 'ê' character. It works with all the input methods provided by the operating system, even the most specific or complex ones.

This event is typically used to catch user input in a text field.

The member associated with this event is `event.text` which contains the Unicode value of the entered character. You can either put it directly in a `sf::String` or cast it to a `char` after making sure that it is in the ASCII range (0 - 127).

```cpp
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128)
            std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
    }
```

NOTE: since they are part of the Unicode standard, some non-printable characters such as backspace are generated by this event. In most cases you will need to filter them out.

#### The KeyPressed and KeyReleased events

The `sf::Event::KeyPressed` and `sf::Event::KeyRelease`d events are triggered when a keyboard key is pressed/released.

If a key is held, multiple `KeyPressed` events will be generated at the default operating system delay (the same delay that applies when you hold a letter in a text editor). To disable repeated `KeyPressed` events, you can call `window.setKeyRepeatEnabled(false)`. On the flip side, it is obvious that `KeyReleased` events can never be repeated.

This event is the one to use if you want to trigger an action _exactly once_ when a key is pressed or released such as making a character jump with space or exiting something with escape.

The member associated with these events is `event.key` which contains the code of the pressed/released key as well as the current state of the modifier keys (alt, control, shift, system).

```cpp
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            std::cout << "the escape key was pressed" << std::endl;
            std::cout << "control:" << event.key.control << std::endl;
            std::cout << "alt:" << event.key.alt << std::endl;
            std::cout << "shift:" << event.key.shift << std::endl;
            std::cout << "system:" << event.key.system << std::endl;
        }
    }
```

NOTE: some keys have a special meaning for the operating system and will lead to unexpected behavior. An example is the F10 key on Windows which "steals" the focus or the F12 key which starts the debugger when using Visual Studio. This will probably be solved in a future version of SFML.

#### The MouseWheelScrolled event

The `sf::Event::MouseWheelScrolled` event is triggered when a mouse wheel moves up or down, but also laterally if the mouse supports it.

The member associated with this event is `event.mouseWheelScroll` which contains the number of ticks the wheel has moved, what the orientation of the wheel is, and the current position of the mouse cursor.

```cpp
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            std::cout << "wheel type: vertical" << std::endl;
        else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
            std::cout << "wheel type: horizontal" << std::endl;
        else
            std::cout << "wheel type: unknown" << std::endl;
        std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
        std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
        std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
    }
```

#### The MouseButtonPressed and MouseButtonReleased events

The `sf::Event::MouseButtonPressed` and `sf::Event::MouseButtonReleased` events are triggered when a mouse button is pressed/released.

SFML supports 5 mouse buttons: left, right, middle (wheel), extra #1 and extra #2 (side buttons).

The member associated with these events is `event.mouseButton` which contains the code of the pressed/released button as well as the current position of the mouse cursor.

```cpp
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Right) {
            std::cout << "the right button was pressed" << std::endl;
            std::cout << "mouse x: " << event.mouseButton.x << std::endl;
            std::cout << "mouse y: " << event.mouseButton.y << std::endl;
        }
    }
```

#### The MouseMoved event

The `sf::Event::MouseMoved` event is triggered when the mouse moves within the window.

This event is triggered even if the window is not focused. However, it is triggered only when the mouse moves within the inner area of the window, not when it moves over the title bar or borders.

The member associated with this event is` event.mouseMove` which contains the current position of the mouse cursor relative to the window.

```cpp
    if (event.type == sf::Event::MouseMoved) {
        std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
        std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
    }
```

#### The MouseEntered and MouseLeft event

The `sf::Event::MouseEntered` and `sf::Event::MouseLeft` events are triggered when the mouse cursor enters/leaves the window.

There is no member associated with these events in the `sf::Event` union.

```cpp
    if (event.type == sf::Event::MouseEntered)
        std::cout << "the mouse cursor has entered the window" << std::endl;

    if (event.type == sf::Event::MouseLeft)
        std::cout << "the mouse cursor has left the window" << std::endl;
```

#### The JoystickButtonPressed and JoystickButtonReleased events

#### The JoystickMoved event

#### The JoystickConnected and JoystickDisconnected events


### Using OpenGL in a SFML window

This tutorial is not about OpenGL itself but how to use SFML as an environment for OpenGL and how to mix them together.

As you know, one of the most important features of OpenGL is portability. But OpenGL alone will not be enough to create complete programs: you need a window, a rendering context, user input, etc. You would have no choice but to write OS-specific code to handle this stuff on your own. This is where the `sfml-window` module comes into play. Let us see how it allows you to play with OpenGL.

#### Including and linking OpenGL to your application

OpenGL headers are not the same on every OS. Therefore, SFML provides an abstract header that takes care of including the right file for you.

```cpp
    #include <SFML/OpenGL.hpp>
```

This header includes OpenGL functions and nothing else. People sometimes think that SFML automatically includes OpenGL extension headers because SFML loads extensions itself, but it is an implementation detail. From the user's point of view, OpenGL extension loading must be handled like any other external library.

You will then need to link your program to the OpenGL library. Unlike what it does with the headers, SFML cannot provide a unified way of linking OpenGL. Therefore, you need to know which library to link to according to what operating system you are using ("opengl32" on Windows, "GL" on Linux, etc.).

NOTE: OpenGL functions start with the "gl" prefix. Remember this when you get linker errors, it will help you find which library you forgot to link.

#### Creating an OpenGL window

Since SFML is based on OpenGL, its windows are ready for OpenGL calls without any extra effort.

```cpp
sf::Window window(sf::VideoMode(800, 600), "OpenGL");

// it works out of the box
glEnable(GL_TEXTURE_2D);
```
In case you think it is too automatic, the `sf::Window` constructor has an extra argument that allows you to change the settings of the underlying OpenGL context. This argument is an instance of the `sf::ContextSettings` structure which provides access to the following settings:

- depthBits is the number of bits per pixel to use for the depth buffer (0 to disable it)
- stencilBits is the number of bits per pixel to use for the stencil buffer (0 to disable it)
- antialiasingLevel is the multisampling level
- majorVersion and minorVersion comprise the requested version of OpenGL

If any of these settings is not supported by the graphics card, SFML tries to find the closest valid match. For example, if 4x anti-aliasing is too high, it tries 2x and then falls back to 0.

In any case, you can check what settings SFML actually used with the `getSettings` function:

#### A typical OpenGL-with-SFML program

Here is what a complete OpenGL program would look like with SFML:

