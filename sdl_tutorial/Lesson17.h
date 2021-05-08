/*
 * Lesson 17: Mouse Events
 * We learn to read mouse input using mouse events.
 * 
 * Like key presses, SDL has event structures to handle mouse events 
 * such as mouse motion, mouse button presses, and mouse button releasing. 
 * 
 * Here we make a several buttons that we can interact with.
 */
#pragma once

#ifndef __LESSON17_H__
#define __LESSON17_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <cmath>

#include "LTexture.h"

using namespace std;


// We will have 4 buttons on the screen. 
// We will display a different sprite on mouse over, 
// click, release, or mouse out for each button.
enum LButtonSprite {
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

// Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int NUM_BUTTONS = 4;


class Lesson17 : public Lesson {
private:
	//static Lesson17 _instance;

	friend class LButton;

	// Mouse button sprites
	SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
	LTexture* gButtonSpriteSheetTexture;

	LButton *gButtons[NUM_BUTTONS];			// array of Button pointers

private:
	bool loadMedia();								// Load media
	void close();									// Free media and shut down SDL

public:
	Lesson17();
	int main(int argc, char* args[]);
};


// Texture wrapper class
// We wrap the SDL_Texture in a class to make some things easier.
// If we want to get certain information about the texture such as its width or height 
// we would have to use some SDL functions to query the information for the texture.
// So we use a class to wrap and store the information about the texture.
class LTexture17 {
public:
	LTexture17();				// initialize variables		
	~LTexture17();				// deallocate memory

	LTexture17(Lesson17* ptr);

	bool loadFromFile(std::string path);										// Load image from specified path

	void free();										// Deallocate texture

	void setColor(Uint8 red, Uint8 green, Uint8 blue);	// Set color modulation
	void setBlendMode(SDL_BlendMode blending);			// Set blending
	void setAlpha(Uint8 alpha);							// Set alpha modulation

	// Render texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
		SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Get image dimensions
	int getWidth();
	int getHeight();

private:
	Lesson17* root;

	SDL_Texture* mTexture;	// pointer to the actual hardware texture

	// image dimensions
	int mWidth;
	int mHeight;
};


// The mouse button
class LButton {
public:
	// Initialize internal variables
	LButton();

	LButton(Lesson17* ptr);

	void setPosition(int x, int y);		// Set top left position	
	void handleEvent(SDL_Event* e);		// Handle mouse event	
	void render();						// Show button sprite

private:
	Lesson17* root;

	SDL_Point mPosition;			// Top left position	
	LButtonSprite mCurrentSprite;	// Currently used global sprite
};

#endif
