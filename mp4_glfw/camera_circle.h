/*
 * camera_circle.h
 * Simple camera example
 */
#pragma once

#ifndef camera_circle_H_
#define camera_circle_H_

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class camera_circle {
private:
	static void process_input(GLFWwindow* window);
	static void resize(GLFWwindow* window, int width, int height);

public:
	camera_circle();
	static int main_gl();
};

#endif // !camera_circle_H_

