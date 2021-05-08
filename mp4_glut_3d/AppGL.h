/*
 * AppGL.h
 * Class wrapper for OpenGL application
 */
#pragma once

 // Demonstration of #include guard idiom.
#ifndef APPGL_H_
#define APPGL_H_

#include <GL/freeglut.h>
//#include <GL/glut.h>  // GLUT includes glu.h and gl.h

enum class Move_Direction { left, right, up, down, in, out };
enum class Rotate_Axis { X, Y, Z };

class AppGL {
private:
    static void init(void);
    static void display(void);
    static void keyboard(unsigned char key, int x, int y);
    static void resize(int width, int height);

    static void Draw(void);
    static void Zoom(float scale);
    static void DrawCube(void);

    static void translate(Move_Direction direction);     // Translation: left, right, up, down
    static void scale(Move_Direction direction);         // Scale: in / out
    static void rotate(float angle, Rotate_Axis axis);   // Rotate about the given axis
    static void elevate(Rotate_Axis axis);               // Show elevation view
    static void reset(void);

    static int read_file(std::string filename);
    static int world_to_screen(void);
    static int window_to_viewport(void);
    static int run(int argc, char** argv, std::string filename);

public:
    AppGL();
    static int main_gl(int argc, char** argv);
};


#endif // !APPGL_H_

