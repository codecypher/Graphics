/*
 * AppGL.h
 * Class wrapper for OpenGL application
 */
#pragma once

 // Demonstration of #include guard idiom.
#ifndef APPGL_H_
#define APPGL_H_

//#include <windows.h> // must include this before GL/gl.h
#include <GL/glut.h>  // GLUT includes glu.h and gl.h

#include <math.h>

class AppGL;  // forward declaration (circular dependency)

enum class Move_Direction { left, right, up, down, in, out };
enum class Rotate_Axis { X, Y, Z };

class AppGL {
private:
    static void init(void);
    static void display(void);
    static void keyboard(unsigned char key, int x, int y);
    static void resize(int width, int height);

    static void Draw(void);
    static void DrawCube(void);

    static void move(Move_Direction direction);
    static void rotate(float angle, Rotate_Axis axis);
    static void reset(void);

    static int read_file(std::string filename);
    static int create_polygon_list(void);
    static int run(int argc, char** argv, std::string filename);

public:
    AppGL();
    static int main_gl(int argc, char** argv);
};


#endif // !APPGL_H_

