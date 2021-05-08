/*
 * Lesson 10: Color Keying
 * Here we use color keying to give textures transparent backgrounds.
 * 
 * When rendering multiple images on the screen, it is usually necessary 
 * to have images with transparent backgrounds. 
 * SDL provides an easy way to do this using color keying.
 */
#pragma once

#ifndef __LESSON10_H__
#define __LESSON10_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>

#include "Lesson.h"

using namespace std;

class Lesson10 : public Lesson {
private:
	// Scene textures
	LTexture* gFooTexture;
	LTexture* gBackgroundTexture;

private:
	bool init();								// Start SDL and create window
	bool loadMedia();							// Load media
	void close();								// Free media and shut down SDL
	SDL_Texture* loadTexture(string path);		// Load image as texture

public:
	Lesson10();
	int main(int argc, char* args[]);
};


#endif