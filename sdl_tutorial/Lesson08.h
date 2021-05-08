/*
 * Lesson 08: Geometry Rendering
 * Another new feature in SDL 2.0 is hardware accelerated primitive rendering. 
 * We use primitve rendering to render some common shapes. 
 */
#pragma once

#ifndef __LESSON8_H__
#define __LESSON8_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>
#include <cmath>

using namespace std;

class Lesson08 {
private:
	static Lesson08 _instance;

	// Screen dimensions
	const int ScreenWidth = 640;
	const int ScreenHeight = 480;

	SDL_Window* gWindow = NULL;				// The window wee will be rendering to
	SDL_Renderer* gRenderer = NULL;			// The window renderer

private:
	Lesson08();

	bool init();									// Start SDL and create window
	bool loadMedia();								// Load media
	void close();									// Free media and shut down SDL
	SDL_Texture* loadTexture(std::string path);		// Load image as texture

public:
	int main(int argc, char* args[]);

	static Lesson08* GetInstance();
};

#endif
