/*
 * Lesson 29: Circular Collision Detection
 * We learn to detect collisions with circles and boxes.
 * 
 * Along with collision boxes, circles are the most common form of collider. 
 * We check for collision between two circles and a circle and a box.
 * 
 * For circle/circle collision, check whether the distance between the center of each circle 
 * is less than the sum of their radii (radii is the plural for radius).
 *
 * For box/circle collision, find the point on the collision box that is closest to the center of the circle. 
 * If that point is less than the radius of the circle, there is a collision.
 */
#pragma once

#ifndef __LESSON29_H__
#define __LESSON29_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <cmath>

#include "Lesson.h"
#include "LTexture.h"
#include "LDot.h"

class Lesson29 : public Lesson {
private:

private:
	bool loadMedia();		// Load media
	void close();			// Free media and shut down SDL

	// Circle/Circle collision detector
	bool checkCollision(LCircle& a, LCircle& b);

	// Circle/Box collision detector
	bool checkCollision(LCircle& a, SDL_Rect& b);

	// Calculate distance squared between two points
	double distanceSquared(int x1, int y1, int x2, int y2);

public:
	Lesson29();
	int main(int argc, char* args[]);
};



#endif
