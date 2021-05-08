/*
 * AppGlut.hpp
 * Class wrapper for OpenGL application using GLUT
 */
#pragma once

// Demonstration of #include guard idiom.
#ifndef __APPGL_H_
#define __APPGL_H_

//#include <windows.h> // must include this before GL/gl.h
#include <GL/glut.h>  // GLUT includes glu.h and gl.h

#include <math.h>

class AppGL;  // forward declaration (circular dependency)

enum class Move_Direction { left, right, up, down, in, out };
enum class Rotate_Axis { X, Y, Z };

class AppGL {
private:
	// Constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const float SCALE_FACTOR = 0.003f;
	const int WORLD_SIZE = 2000;
	const int MAX = 100;
	const float DEFAULT = 20.0f;

	float _zview = 0.5f;
	float _aspect = 1.0f;
	float _width = 0.0f;
	float _height = 0.0f;
	float _zoom = 1.0f;
	float _anglex = 0.0f;
	float _angley = 0.0f;
	float _anglez = 0.0f;

	std::vector<std::vector<float>> _vPoints;   // vector list

private:
	virtual void init();
	virtual	void display();
	virtual void keyboard(unsigned char key, int x, int y);
	virtual void reshape(int width, int height);

	void print_vector(int n = 5);
	void move(Move_Direction direction);
	void rotate(float angle, Rotate_Axis axis);
	void reset();

	int read_file(std::string filename);
	int run(int argc, char** argv, std::string filename);

public:
	AppGL();
	int main_gl(int argc, char** argv);
};



#endif // !__APPGL_H_

