/*
 * Lesson 28: Per-pixel Collision Detection
 * We have two objects collide using per-pixel collision detection.
 * 
 * Once we know how to check collision between two rectangles, 
 * we can check collision between any two images 
 * since all images are made out of rectangles.
 */
#pragma once

#ifndef __LESSON28_H__
#define __LESSON28_H__

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

class Lesson28 : public Lesson {
private:

private:
	bool loadMedia();		// Load media
	void close();			// Free media and shut down SDL

	// Box collision detector
	bool checkPixelCollision(std::vector<SDL_Rect> &a, std::vector<SDL_Rect> &b);	

public:
	Lesson28();
	int main(int argc, char* args[]);
};


#endif
	