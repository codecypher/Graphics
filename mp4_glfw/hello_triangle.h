/*
 * hello_triangle.h
 * Simple example
 */
#pragma once

#ifndef hello_triangle_H_
#define hello_triangle_H_

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class hello_triangle {
private:
	static void process_input(GLFWwindow* window);
	static void resize(GLFWwindow* window, int width, int height);

public:
	hello_triangle();
	static int main_gl();
};


#endif // !hello_triangle_H_

