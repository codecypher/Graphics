/*
 * Lesson.h
 * Base class for Lessons 10-18
 */
#pragma once

#ifndef __LESSON_H__
#define __LESSON_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <sstream>
#include <vector>

#include <stdio.h>

#include "LTexture.h"
#include "LCircle.h"


class Lesson {
protected:
	//static Lesson _instance;

	friend class LTexture;
	friend class LDot;
	friend class LWindow;

	// Screen dimensions
	const int ScreenWidth = 640;
	const int ScreenHeight = 480;

	// The dimensions of the level
	const int LEVEL_WIDTH = 1280;
	const int LEVEL_HEIGHT = 960;

	SDL_Window* gWindow = NULL;				// The window we will be rendering to
	SDL_Renderer* gRenderer = NULL;			// The window renderer	
	TTF_Font* gFont = NULL;					// Globally used font

	// Scene textures
	LTexture* gDotTexture = NULL;

	virtual bool init();					// Start SDL and create window
	virtual bool loadMedia();				// Load media
	virtual void close();					// Free media and shut down SDL

	// Box collision detectors
	virtual bool checkCollision(SDL_Rect *a, SDL_Rect *b);
	virtual bool checkPixelCollision(std::vector<SDL_Rect> &a, std::vector<SDL_Rect> &b);

	// Circle/Circle collision detector
	virtual bool checkCollision(LCircle& a, LCircle& b);

	// Circle/Box collision detector
	virtual bool checkCollision(LCircle& a, SDL_Rect& b);

	// Calculate distance squared between two points
	virtual double distanceSquared(int x1, int y1, int x2, int y2);

public:
	Lesson();
	virtual int main(int argc, char* args[]);
	//static Lesson* GetInstance();
};


#endif