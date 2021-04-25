/*
 * ex6.c
 * Example 6: A rotating cube
 */
#ifndef ex6_h
#define ex6_h

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>

#include <stdio.h>
#include <stdlib.h>

void spin (void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
int main_ex6(int argc, char** argv);


#endif /* ex6_h */
