/*
 * Lesson 4: Key Presses
 * We learn to handle keyboard input.
 */
#pragma once

#ifndef __LESSON4_H__
#define __LESSON4_H__

#include <SDL2/SDL.h>

#include <stdio.h>
#include <string>

using namespace std;

class Lesson04 {
private:
	static Lesson04 _instance;

	// Screen dimensions
	const int ScreenWidth = 640;
	const int ScreenHeight = 480;

	// Keypress surfaces constants
	enum KeyPressSurfaces {
		KEY_PRESS_SURFACE_DEFAULT,
		KEY_PRESS_SURFACE_UP,
		KEY_PRESS_SURFACE_DOWN,
		KEY_PRESS_SURFACE_LEFT,
		KEY_PRESS_SURFACE_RIGHT,
		KEY_PRESS_SURFACE_TOTAL
	};

	SDL_Window* gWindow = NULL;									// The window wee will be rendering to
	SDL_Surface* gScreenSurface = NULL;							// The surface contained by the window
	SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];	// The images that correspond to a keypress (array of surfaces)
	SDL_Surface* gCurrentSurface = NULL;						// Current displayed image

private:
	Lesson04();

	bool init();			// Start SDL and create window
	bool loadMedia();		// Load media
	void close();			// Free media and shuts down SDL

	SDL_Surface* loadSurface(string path);

public:
	int main(int argc, char* args[]);

	static Lesson04* GetInstance();
};

#endif

