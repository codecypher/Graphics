/*
 * hello_triangle_indexed.h
 * Simple example
 */
#pragma once

#ifndef hello_triangle_indexed_H_
#define hello_triangle_indexed_H_

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void process_input_triangle_indexed(GLFWwindow* window);
void resize_triangle_indexed(GLFWwindow* window, int width, int height);
int hello_triangle_indexed();

#endif // !hello_triangle_indexed_H_

