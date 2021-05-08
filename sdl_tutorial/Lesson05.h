/*
 * Lesson 5: Optimized Surface Loading and Soft Stretching
 * Now that we know how to load and blit surfaces, we make our blits faster. 
 * We also take a smaller image and stretch it to fit the screen.
 */
#pragma once

#ifndef __LESSON5_H__
#define __LESSON5_H__

#include <SDL2/SDL.h>

#include <stdio.h>
#include <string>

using namespace std;

class Lesson05 {
private:
	static Lesson05 _instance;

	// Screen dimensions
	const int ScreenWidth = 640;
	const int ScreenHeight = 480;

	SDL_Window* gWindow = NULL;				// The window wee will be rendering to
	SDL_Surface* gScreenSurface = NULL;		// The surface contained by the window
	SDL_Surface* gStretchedSurface = NULL;	// Current displayed image

private:
	Lesson05();

	bool init();								// Start SDL and create window
	bool loadMedia();							// Load media
	void close();								// Free media and shuts down SDL
	SDL_Surface* loadSurface(string path);		// Load image at specified path

public:
	int main(int argc, char* args[]);

	static Lesson05* GetInstance();
};

#endif


