/*
 * Lesson 26: Motion
 * We use what we learned about rendering and handling input 
 * to make a dot move around the screen.
 */
#pragma once

#ifndef __LESSON26_H__
#define __LESSON26_H__

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


class Lesson26 : public Lesson {
private:	

private:
	bool loadMedia();		// Load media
	void close();			// Free media and shut down SDL

public:
	Lesson26();
	int main(int argc, char* args[]);
};


#endif
