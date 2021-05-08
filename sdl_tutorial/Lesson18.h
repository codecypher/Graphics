/*
 * Lesson 18: Key States
 * There are other ways to read the keys besides event polling. 
 * We can get the current state of the keyboard using key states.
 * 
 * There are ways to get the state of the input devices (mouse, keyboard, etc) other than using events.
 * Here we redo the keyboard input tutorial using key states rather than events.
 */
#pragma once

#ifndef __LESSON18_H__
#define __LESSON18_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <cmath>

#include "Lesson.h"
#include "LTexture.h"

using namespace std;


class Lesson18 : public Lesson {
private:
	// Scene textures
	LTexture* gPressTexture;
	LTexture* gUpTexture;
	LTexture* gDownTexture;
	LTexture* gLeftTexture;
	LTexture* gRightTexture;

private:
	bool loadMedia();		// Load media
	void close();			// Free media and shut down SDL

public:
	Lesson18();
	int main(int argc, char* args[]);
};


#endif
