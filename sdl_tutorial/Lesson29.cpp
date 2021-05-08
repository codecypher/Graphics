#include "Lesson29.h"


Lesson29::Lesson29() {
	gDotTexture = new LTexture(this);
}


// We want to minimize the amount of times that we render text. 
bool Lesson29::loadMedia() {
	bool success = true;	// Loading success flag

	// Load dot texture
	if (!gDotTexture->loadFromFile("img/dot.bmp")) {
		printf("Failed to load dot texture!\n");
		success = false;
	}

	return success;
}


void Lesson29::close() {
	// Free loaded images
	gDotTexture->free();

	__super::close();
}


// Circle/Circle collision detector
// Check if the distance squared between the centers is less than the sum of the radii squared. 
// If it is, there is a collison.
bool Lesson29::checkCollision(LCircle& a, LCircle& b) {
	// Calculate total radius squared
	int totalRadiusSquared = a.r + b.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

	// If the distance between the centers of the circles is less than the sum of their radii
	if (distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared)) {	
		return true;	// The circles have collided
	}

	return false;
}

// Circle/Box collision detector
// To check if a box and circle collided we need to find the closest point on the box (3 cases).
bool Lesson29::checkCollision(LCircle& a, SDL_Rect& b) {
	// Closest point on collision box
	int cX, cY;

	// Find closest x offset
	if (a.x < b.x) {
		cX = b.x;
	}
	else if (a.x > b.x + b.w) {
		cX = b.x + b.w;
	}
	else {
		cX = a.x;
	}

	// Find closest y offset
	if (a.y < b.y) {
		cY = b.y;
	}
	else if (a.y > b.y + b.h) {
		cY = b.y + b.h;
	}
	else {
		cY = a.y;
	}

	// If the closest point is inside the circle
	if (distanceSquared(a.x, a.y, cX, cY) < a.r * a.r) {	
		return true;	// This box and the circle have collided
	}

	return false;
}

// Calculate distance squared between two points
// Why are we using the distance squared as opposed to the plain distance? 
// Calculating the distance involves a square root which is a relatively expensive operation.
// However, if x > y then x^2 > y^2, so we can just compare the distance squared.
double Lesson29::distanceSquared(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}



int Lesson29::main(int argc, char* args[]) {
	// Startup SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		// Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			bool quit = false;		// Main loop flag			
			SDL_Event e;			// Event handler

			// The dot that will be moving around on the screen
			LDot dot(LDot::DOT_WIDTH / 2, LDot::DOT_HEIGHT / 2, this, true);

			// The dot that will be collided against
			LDot otherDot(ScreenWidth / 4, ScreenHeight / 4, this, true);

			// Set the wall
			SDL_Rect wall;
			wall.x = 300;
			wall.y = 40;
			wall.w = 40;
			wall.h = 400;

			// While application is running
			while (!quit) {
				// Handle events on queue (event/game queue)
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}

					dot.handleEvent(e);		// Handle input for the dot
				}

				// Move the dot and check collision
				dot.move(wall, otherDot.getCollider());

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render wall
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderDrawRect(gRenderer, &wall);

				// Render dots
				dot.render(true);
				otherDot.render(true);

				SDL_RenderPresent(gRenderer);	// Update screen
			}
		}
	}

	close();	// Free resources and close SDL

	return 0;
}

