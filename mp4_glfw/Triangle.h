/*
 * Triangle.h
 * GLFW Getting started
 * 
 * Rotating triangle
 * 
 * Reference: https://www.glfw.org/docs/latest/quick.html
 */
#pragma once

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Triangle {
private:
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	Triangle();
	static int main_gl(int argc, char** argv);
};



#endif // !TRIANGLE_H_

