/*
 * Square.h
 * Class wrapper for OpenGL application using GLFW and Glad
 *
 * Rotating circle of squares
 * 
 * The program creates a 640 by 480 windowed mode window
 * and starts a loop that clears the screen, renders a square,
 * and processes events until the user presses Escape or closes the window.
 */
#pragma once

#ifndef SQUARE_H_
#define SQUARE_H_

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>


class RotateSquares {
private:
	static const int SCREEN_WIDTH, SCREEN_HEIGHT, WORLD_SIZE;
	static const float rotations_per_tick;
	static float rotate_y, rotate_z, prev_time;

private:
	static void Init();
	static void Draw_Squares(float red, float green, float blue);
	static void Draw();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void resize_callback(GLFWwindow* window, int width, int height);

public:
	RotateSquares();
	static int main_gl(int argc, char** argv);
};


#endif // !SQUARE_H_

