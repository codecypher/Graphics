/*
 * AppSDL.hpp
 * Class wrapper for SDL application
 * 
 * Lesson 04: Key Presses
 * Lesson 18: Key States
 * Learn to handle keyboard input
 */
#pragma once

#ifndef __APPSDL_H__
#define __APPSDL_H__

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

#include "LTexture.hpp"


class AppSDL {
protected:
	friend class LTexture;

	// Screen dimensions
	const int ScreenWidth = 640;
	const int ScreenHeight = 480;

	SDL_Window* gWindow = NULL;			// The window we will be rendering to
	SDL_Renderer* gRenderer = NULL;		// The window renderer	

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

private:
	int main_sdl(int argc, char* args[]);

public:
	AppSDL();
	int main(int argc, char* args[]);
};


#endif // !__APPSDL_H__
