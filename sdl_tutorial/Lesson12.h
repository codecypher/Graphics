/*
 * Lesson 12: Color Modulation
 * We alter the color of rendered textures using color modulation.
 * 
 * Color modulation allows you to alter the color of your rendered textures.
 * We modulate a texture using various colors.
 */
#pragma once

#ifndef __LESSON12_H__
#define __LESSON12_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>

#include "LTexture.h"

using namespace std;

class Lesson12 : public Lesson {
private:
	LTexture* gModulatedTexture;	// scene texture

private:
	bool loadMedia();				// Load media
	void close();					// Free media and shut down SDL

public:
	Lesson12();
	int main(int argc, char* args[]);
};

#endif
