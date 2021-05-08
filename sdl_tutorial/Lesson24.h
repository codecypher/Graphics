/*
 * Lesson 24: Calculating Frame Rate
 * We use the timers we built to measure frame rate.
 */
#pragma once

#ifndef __LESSON24_H__
#define __LESSON24_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <cmath>

#include "Lesson.h"
#include "LTexture.h"
#include "LTimer.h"

using namespace std;


class Lesson24 : public Lesson {
private:
	LTexture* gFPSTextTexture;	// Scene texture

private:
	bool loadMedia();		// Load media
	void close();			// Free media and shut down SDL

public:
	Lesson24();
	int main(int argc, char* args[]);
};


#endif
