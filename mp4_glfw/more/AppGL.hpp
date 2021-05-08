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
	// Constants
	static const int SCREEN_WIDTH;
	static const int SCREEN_HEIGHT;
	static const int WORLD_SIZE;
	static const int MAX;

	const static float SCALE_FACTOR;
	const static float DEFAULT;

	static float _zview;
	static float _aspect;
	static float _width;
	static float _height;
	static float _zoom;
	static float _anglex;
	static float _angley;
	static float _anglez;

	static std::vector<std::vector<float>> _vPoints;   // vector list

private:
	static void Init();
	static void Draw();
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void resize_callback(GLFWwindow* window, int width, int height);

	static void print_vector(int n = 5);
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

