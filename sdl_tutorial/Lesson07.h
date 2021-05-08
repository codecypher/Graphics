/*
 * Lesson 7: Texture Loading and Rendering
 * A new feature in SDL 2.0 is hardware accelerated texture based 2D rendering. 
 * We load an image and render it using textures. 
 */
#pragma once

#ifndef __LESSON7_H__
#define __LESSON7_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>

using namespace std;

class Lesson07 {
private:
	static Lesson07 _instance;

	// Screen dimensions
	const int ScreenWidth = 640;
	const int ScreenHeight = 480;

	SDL_Window* gWindow = NULL;				// The window wee will be rendering to
	SDL_Renderer* gRenderer = NULL;			// The window renderer
	SDL_Texture* gTexture = NULL;			// Current displayed texture

private:
	Lesson07();

	bool init();									// Start SDL and create window
	bool loadMedia();								// Load media
	void close();									// Free media and shut down SDL
	SDL_Texture* loadTexture(std::string path);		// Load image as texture

public:
	int main(int argc, char* args[]);

	static Lesson07* GetInstance();
};

#endif


