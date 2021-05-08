/*
 * Lesson 30
 * Scrolling
 * Implement a camera to scroll levels larger than the screen. 
 */
#pragma once

#ifndef LESSON30_H__
#define LESSON30_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <cmath>

#include "Lesson.h"
#include "LTexture.h"
#include "LDot.h"

using namespace std;

class Lesson30 : public Lesson {
private:
	// Scene textures
	LTexture* gBGTexture = NULL;

private:
	bool loadMedia();		// Load media
	void close();			// Free media and shut down SDL

public:
	Lesson30();
	int main(int argc, char* args[]);
};


#endif
