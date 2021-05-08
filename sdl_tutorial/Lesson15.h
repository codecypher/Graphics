/*
 * Lesson 15: Rotation and Flipping
 * We use SDL 2.0's new texture rotation and flipping.
 * 
 * SDL 2 hardware accelerated texture rendering can give us fast image flipping and rotation. 
 * We use this feature to make an arrow texture spin and flip.
 */
#pragma once

#ifndef __LESSON15_H__
#define __LESSON15_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>
#include <cmath>

#include "LTexture.h"

using namespace std;

class Lesson15 : public Lesson {
private:
	LTexture* gArrowTexture;		// scene texture

private:
	bool loadMedia();				// Load media
	void close();					// Free media and shut down SDL

public:
	Lesson15();
	int main(int argc, char* args[]);
};

#endif
