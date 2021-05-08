/*
 * Lesson 9: The Viewport
 * SDL 2.0 lets you control where you render on the screen using the viewport.
 * We use the viewport to create subscreens.
 */
#pragma once

#ifndef __LESSON9_H__
#define __LESSON9_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>

using namespace std;

class Lesson09 {
private:
	static Lesson09 _instance;

	// Screen dimensions
	const int ScreenWidth = 1024;
	const int ScreenHeight = 768;

	SDL_Window* gWindow = NULL;				// The window wee will be rendering to
	SDL_Renderer* gRenderer = NULL;			// The window renderer
	SDL_Texture* gTexture = NULL;			// Current displayed texture

private:
	Lesson09();

	bool init();									// Start SDL and create window
	bool loadMedia();								// Load media
	void close();									// Free media and shut down SDL
	SDL_Texture* loadTexture(std::string path);		// Load image as texture

public:
	int main(int argc, char* args[]);

	static Lesson09* GetInstance();
};

#endif
