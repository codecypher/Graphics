/**
 * Lesson 3: Event Driven Programming
 * We start handling user input by allowing the user to X out (close) the window.
 */
#pragma once

#ifndef __LESSON3_H__
#define __LESSON3_H__

#include <SDL2/SDL.h>

#include <stdio.h>

using namespace std;

class Lesson03 {
private:
	static Lesson03 _instance;

	// Screen dimensions
	const int ScreenWidth = 640;
	const int ScreenHeight = 480;

	SDL_Window* gWindow = NULL;				// The window wee will be rendering to
	SDL_Surface* gScreenSurface = NULL;		// The surface contained by the window
	SDL_Surface* gXOut = NULL;				// The image to load and show on the screen

private:
	Lesson03();

	bool init();			// Start SDL and create window
	bool loadMedia();		// Load media
	void close();			// Free media and shuts down SDL

public:
	int main(int argc, char* args[]);

	static Lesson03* GetInstance();
};

#endif