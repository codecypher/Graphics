/*
 * Lesson 27: Collision Detection
 * We have two objects interact with each other using bounding box collision detection.
 * 
 * In games you often need to tell if two objects hit each other. 
 * For simple games, this is usually done with bounding box collision detection.
 */
#pragma once

#ifndef __LESSON27_H__
#define __LESSON27_H__

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


class Lesson27 : public Lesson {
private:

private:
	bool loadMedia();		// Load media
	void close();			// Free media and shut down SDL

	bool checkCollision(SDL_Rect* a, SDL_Rect* b);	// Box collision detector

public:
	Lesson27();
	int main(int argc, char* args[]);
};


#endif
