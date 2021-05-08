/**
 * Lesson 2: Getting an Image on the Screen
 * Now that we can get a window to appear, we blit an image onto it.
 */
#pragma once

#ifndef __LESSON2_H__
#define __LESSON2_H__

#include <SDL2/SDL.h>

#include <stdio.h>

class Lesson02 {
private:
	static Lesson02 _instance;

	bool Running = true;

	SDL_Window* gWindow = NULL;				// The window wee will be rendering to
	SDL_Surface* gScreenSurface = NULL;		// The surface contained by the window
	SDL_Surface* gHelloWorld = NULL;		// The image to load and show on the screen

	// Screen dimensions
	const int ScreenWidth = 640;
	const int ScreenHeight = 480;

private:
	Lesson02();

	bool init();			// Start SDL and create window
	bool loadMedia();		// Load media
	void close();			// Free media and shuts down SDL

public:
	int main(int argc, char* args[]);

	static Lesson02* GetInstance();

	//SDL_Surface* GetScreen();
	//SDL_Surface* GetImage();

	//static int GetScreenWidth();
	//static int GetScreenHeight();
};

#endif