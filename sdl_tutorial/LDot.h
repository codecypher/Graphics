#pragma once

#ifndef __LDOT_H__
#define __LDOT_H__

//#include <SDL2/SDL.h>

#include "Lesson.h"
#include "LCircle.h"

class Lesson;  // forward declaration (circular dependency)


// The dot that will move around on the screen
class LDot {
public:
	// The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	// Maximum axis velocity of the dot
	int DOT_VEL = 10;

	// Initialize the variables
	//LDot();
	LDot(Lesson* ptr);
	LDot(int x, int y, Lesson* ptr = NULL, bool useCircles = false);

	// Handle key presses and adjust the dot velocity
	void handleEvent(SDL_Event& e);
	
	void move_scroll(void);								// Move the dot for scrolling		
	void move(SDL_Rect* wall = NULL);					// Move the dot				
	void move(SDL_Rect& square, LCircle& circle);		// Move the dot and checks collision
	void move(std::vector<SDL_Rect> &otherColliders);	// Move the dot and check collision
	void render(bool useCircle = false);				// Show the dot on the screen
	void render(int camX, int camY);					// Show the dot on the screen relative to the camera

	std::vector<SDL_Rect>& getColliders();				// Get the collision boxes
	LCircle& getCollider();								// Get collision circle

	// Position accessors
	int getPosX();
	int getPosY();

private:
	Lesson* root;
	int mPosX, mPosY;			// The X and Y offsets of the dot	
	int mVelX, mVelY;			// The velocity of the dot

	SDL_Rect* mCollider;		// Dot collision box
	LCircle mColliderCircle;	// Dot collision circle

	// Instead of a single collision box, we have a vector of colliders
	std::vector<SDL_Rect> mColliders;		// Dot collision boxes
	
	void shiftColliders(bool useCircles = false);	// Move the colliders to match the position of the dot		
};


#endif