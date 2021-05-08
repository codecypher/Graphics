/*
 * hello_rotate_triangle.h
 * Simple example
 */
#pragma once

#ifndef hello_rotate_triangle_H_
#define hello_rotate_triangle_H_

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class hello_rotate_triangle {
private:
	static void process_input(GLFWwindow* window);
	static void resize(GLFWwindow* window, int width, int height);

public:
	hello_rotate_triangle();
	static int main_gl();
};


#endif // !hello_rotate_triangle_H_

