/*
 * Lesson 14: Animated Sprites and Vsync
 * We use a sequence of sprites to animate them.
 * 
 * Animation in a nutshell is just showing one image after another 
 * to create the illusion of motion. 
 * We show different sprites to animate a stick figure.
 * 
 * If we show one right after the other every 10th of a second we get an animation.
 * Since images in SDL 2 are typically SDL_Textures, animating in SDL is a matter of 
 * showing different parts of a texture (or different whole textures) one right after the other.
 * 
 * For this (and future tutorials), we want to use Vertical Sync. 
 * VSync allows the rendering to update at the same time that the monitor updates during vertical refresh. 
 * For this tutorial it will make sure the animation does not run too fast. 
 * Most monitors run at about 60 frames per second which is the assumption we're making here. 
 * If you have a different monitor refresh rate the animation may appear to be running too fast or slow.
 */
#pragma once

#ifndef __LESSON14_H__
#define __LESSON14_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>

#include "LTexture.h"

using namespace std;

const int WALKING_ANIMATION_FRAMES = 4;

class Lesson14 : public Lesson {
private:
	// Walking animation
	// We have the spritesheet with sprites 
	// that we are going to use for the animation.
	SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
	LTexture* gSpriteSheetTexture; 

private:
	bool loadMedia();						// Load media
	void close();							// Free media and shut down SDL

public:
	Lesson14();
	int main(int argc, char* args[]);
	static Lesson14* GetInstance();
};

#endif
