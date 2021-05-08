/*
 * Lesson 33
 * File Reading and Writing
 * Using SDL's RWOps API to do binary file IO.
 */
#pragma once

#ifndef LESSON33_H__
#define LESSON33_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <cmath>

#include "Lesson.h"
#include "LTexture.h"


// The data we will be loading and saving
const int TOTAL_DATA = 10;

class Lesson33 : public Lesson {
private:
	bool loadMedia();		// Load media
	void close();			// Free media and shut down SDL

	// Scene textures
	LTexture* gPromptTextTexture;
	LTexture *gDataTextures[TOTAL_DATA];

	// Data points
	Sint32 *gData[TOTAL_DATA];

public:
	Lesson33();
	int main(int argc, char* args[]);
};


#endif
