/*
 * Lesson 22: Timing
 * We use the SDL time capabilites.
 * 
 * Another important part of any sort of gaming API is the ability to handle time. 
 * We make a timer that we can restart.
 */
#pragma once

#ifndef __LESSON22_H__
#define __LESSON22_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <cmath>

#include "Lesson.h"
#include "LTexture.h"

using namespace std;


class Lesson22 : public Lesson {
private:
	// Scene textures
	LTexture* gTimeTextTexture;
	LTexture* gPromptTextTexture;

private:
	bool init();			// Start SDL and create window
	bool loadMedia();		// Load media
	void close();			// Free media and shut down SDL

public:
	Lesson22();
	int main(int argc, char* args[]);
};


#endif
