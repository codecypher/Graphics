/*
 * Lesson 4: Key Presses
 * We learn to handle keyboard input.
 */
#pragma once

#ifndef __APP_H__
#define __APP_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// C++ header files
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>

// C header files
#include <stdio.h>

#include "LTexture.h"


class App {
protected:
	friend class LTexture;

	// Screen dimensions
	const int ScreenWidth = 640;
	const int ScreenHeight = 480;

	SDL_Window* gWindow = NULL;			// The window we will be rendering to
	SDL_Renderer* gRenderer = NULL;		// The window renderer	

	//SDL_Surface* gScreenSurface = NULL;							// The surface contained by the window
	//SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];	// The images that correspond to a keypress (array of surfaces)
	//SDL_Surface* gCurrentSurface = NULL;						// Current displayed image

	// The images that correspond to a keypress
	LTexture* gPressTexture;
	LTexture* gUpTexture;
	LTexture* gDownTexture;
	LTexture* gLeftTexture;
	LTexture* gRightTexture;

protected:
	bool init();			// Start SDL and create window
	bool loadMedia();		// Load media
	void close();			// Free media and shut down SDL

public:
	App();
	int main(int argc, char* args[]);
};

#endif