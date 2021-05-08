/*
 * camera_keyboard.h
 * Simple example
 */
#pragma once

#ifndef camera_keyboard_H_
#define camera_keyboard_H_

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void process_input_camera_keyboard(GLFWwindow* window);
void resize_camera_keyboard(GLFWwindow* window, int width, int height);
int camera_keyboard();

#endif // !camera_keyboard_H_

