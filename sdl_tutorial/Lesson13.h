/*
 * Lesson 13: Alpha Blending
 * We use SDL 2.0 new hardware accelerated alpha blending.
 * 
 * Weuse alpha modulation (which works much like color modulation) 
 * to control the transparency of a texture.
 */
#pragma once

#ifndef __LESSON13_H__
#define __LESSON13_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>

#include "LTexture.h"

using namespace std;

class Lesson13 : public Lesson {
private:
	// Scene textures
	LTexture* gModulatedTexture;
	LTexture* gBackgroundTexture;

private:
	bool loadMedia();		// Load media
	void close();			// Free media and shut down SDL

public:
	Lesson13();
	int main(int argc, char* args[]);
};


#endif
