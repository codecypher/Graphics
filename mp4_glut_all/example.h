/*
 * example.h
 * 3D Graphics with OpenGL By Examples
 * https://www3.ntu.edu.sg/home/ehchua/programming/opengl/CG_Examples.html
 */
#pragma once

#ifndef Example_H_
#define Example_H_

//#include <windows.h> // must include this before GL/gl.h
#include <GL/glut.h>  // GLUT includes glu.h and gl.h

#include <math.h>

class Example {
private:
	// Constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const float SCALE_FACTOR = 0.003f;
	const int WORLD_SIZE = 2000;
	const int MAX = 100;
	const float DEFAULT = 20.0f;

private:
	static void init();
	static void keyboard(unsigned char key, int x, int y);
	static void display();
	static void reshape(int width, int height);

	static void DrawCube(void);
	static void DrawTriangle(void);
public:
	Example();
	static int main_gl(int argc, char** argv);
};



#endif // !Example_H_

