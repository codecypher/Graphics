/*
 * Simple.h
 * Class wrapper for OpenGL application
 * Simple examples using GLFW and Glad
 */
#pragma once

// Demonstration of #include guard idiom.
#ifndef SIMPLE_H_
#define SIMPLE_H_

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Simple {
private:
	static const int SCREEN_WIDTH, SCREEN_HEIGHT, WORLD_SIZE;
	static const float rotations_per_tick;
	static float rotate_y, rotate_z, prev_time;

private:
	static void Init();
	static void DrawSquare();
	static void DrawTriangle();
	static void process_input_simple(GLFWwindow* window, int key, int scancode, int action, int mods);
	//static void resize_callback(GLFWwindow* window, int width, int height);


public:
	Simple();
	static int main_gl(int argc, char** argv);
};



#endif // !SIMPLE_H_

