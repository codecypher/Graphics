/*
 * Lesson 6: Extension Libraries and Loading Other Image Formats
 * We use the SDL_image extension library to load PNG images.
 */
#pragma once

#ifndef __LESSON6_H__
#define __LESSON6_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>

using namespace std;

class Lesson06 {
private:
	static Lesson06 _instance;

	// Screen dimensions
	const int ScreenWidth = 640;
	const int ScreenHeight = 480;

	SDL_Window* gWindow = NULL;				// The window wee will be rendering to
	SDL_Surface* gScreenSurface = NULL;		// The surface contained by the window
	SDL_Surface* gPNGSurface = NULL;		// Current displayed image

private:
	Lesson06();

	bool init();									// Start SDL and create window
	bool loadMedia();								// Load media
	void close();									// Free media and shut down SDL	
	SDL_Surface* loadSurface(std::string path);		// Load image at specified path

public:
	int main(int argc, char* args[]);

	static Lesson06* GetInstance();
};

#endif


