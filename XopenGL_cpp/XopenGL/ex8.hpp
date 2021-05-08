/*
 * ex8.h
 * Draw a tumbling green cube orbiting a stationary red cube
 */
#ifndef ex8_h
#define ex8_h

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>

#include <stdio.h>
#include <stdlib.h>

class Ex8 {
private:
    static void init(void);
    static void spin (void);
    static void display(void);
    static void keyboard(unsigned char key, int x, int y);
    static void reshape(int w, int h);

public:
    int main(int argc, char** argv);
};

#endif /* ex8_h */
