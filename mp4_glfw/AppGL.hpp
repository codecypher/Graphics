/*
 * AppGL.hpp
 * Class wrapper for OpenGL application
 */
#pragma once

 // Using #include guard idiom
#ifndef APPGL_H_
#define APPGL_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class AppGL;  // forward declaration (circular dependency)

enum class Move_Direction { left, right, up, down, in, out };
enum class Rotate_Axis { X, Y, Z };

class AppGL {
private:
	static void init(void);
	static void display(void);
	static void error_callback(int error, const char* description);
	static void process_input(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void resize(GLFWwindow* window, int width, int height);

	static void print_vector(void);
	static void Move(Move_Direction direction);
	static void Rotate(float angle, Rotate_Axis axis);
	static void Reset();

	static int ReadFile(std::string filename);
	static int Run(int argc, char** argv, std::string filename);

public:
	AppGL();
	static int main_gl(int argc, char** argv);
};


#endif // !APPGL_H_

