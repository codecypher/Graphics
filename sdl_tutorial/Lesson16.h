/*
 * Lesson 16:  True Type Fonts
 * We render text from true type fonts using SDL_ttf.
 * 
 * One way to render text with SDL is with the extension library SDL_ttf. 
 * SDL_ttf allows you to create images from TrueType fonts 
 * which we use here to create textures from font text.
 */
#pragma once

#ifndef __LESSON16_H__
#define __LESSON16_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>
#include <cmath>

#include "LTexture.h"

using namespace std;


class Lesson16 : public Lesson {
private:
	LTexture* gTextTexture;		// Rendered texture (texture generated from the font)

private:
	bool init();				// Start SDL and create window
	bool loadMedia();			// Load media
	void close();				// Free media and shut down SDL

public:
	Lesson16();
	int main(int argc, char* args[]);
};

#endif
