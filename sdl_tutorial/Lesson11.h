/*
 * Lesson 11: Clip Rendering and Sprite Sheets
 * Using clip rendering, we can keep multiple images on one texture and render the part we need. 
 * We use this technique to render individual sprites from a sprite sheet. 
 * 
 * Sometimes you only want to render part of a texture. 
 * Many games like to keep multiple images on the same sprite sheet rather than having a bunch of textures. 
 * Using clip rendering, we can define a portion of the texture to render rather than the whole thing.
 */
#pragma once

#ifndef __LESSON11_H__
#define __LESSON11_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>

#include "LTexture.h"

using namespace std;

class Lesson11 : public Lesson {
private:
	// Scene sprites (a texture image and 4 rectangles to define the sprites).
	SDL_Rect gSpriteClips[4];
	LTexture* gSpriteSheetTexture;

private:
	bool loadMedia();								// Load media
	void close();									// Free media and shut down SDL
	SDL_Texture* loadTexture(std::string path);		// Load image as texture

public:
	Lesson11();
	int main(int argc, char* args[]);
};

#endif
