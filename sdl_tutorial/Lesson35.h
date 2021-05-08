/*
 * Lesson 35
 * Window Events
 * Handling events from a resizable window.
 * 
 * SDL also supports resizable windows. 
 * When you have resizable windows there are additional events to handle.
 */
#pragma once

#ifndef LESSON35_H__
#define LESSON35_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <cmath>

#include "Lesson.h"
#include "LTexture.h"
#include "LWindow.h"


class Lesson35 : public Lesson {
private:
	bool init();
	bool loadMedia();		// Load media
	void close();			// Free media and shut down SDL

	// Our custom window
	LWindow* gWindow;
	
	// The window renderer
	//SDL_Renderer* gWinRenderer = NULL;

	// Scene textures
	LTexture* gSceneTexture;
public:
	Lesson35();
	int main(int argc, char* args[]);
};


#endif
