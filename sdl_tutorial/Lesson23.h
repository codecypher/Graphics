/*
 * Lesson 23: Advanced Timers
 * We extend SDL time capabilities to make our own custom timer.
 *
 * Now that we have a basic timer with SDL, we make one that can start/stop/pause.
 */
#pragma once

#ifndef __LESSON23_H__
#define __LESSON23_H__

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


class Lesson23 : public Lesson {
private:
	// Scene textures
	LTexture* gTimeTextTexture;
	LTexture* gStartPromptTexture;
	LTexture* gPausePromptTexture;

private:
	bool init();			// Start SDL and create window
	bool loadMedia();		// Load media
	void close();			// Free media and shut down SDL

public:
	Lesson23();
	int main(int argc, char* args[]);
};


#endif
