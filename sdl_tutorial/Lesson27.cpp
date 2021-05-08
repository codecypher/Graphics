#include "Lesson27.h"


Lesson27::Lesson27() {
	gDotTexture = new LTexture(this);
}


// We want to minimize the amount of times that we render text. 
bool Lesson27::loadMedia() {
	bool success = true;	// Loading success flag

	// Load dot texture
	if (!gDotTexture->loadFromFile("img/dot.bmp")) {
		printf("Failed to load dot texture!\n");
		success = false;
	}

	return success;
}


void Lesson27::close() {
	// Free loaded images
	gDotTexture->free();

	__super::close();
}



// Check collision between two boxes
// 
// Collision boxes are a standard way to check collision between two objects. 
// Two polygons are in collision when they are not separated.
//
// This form of collision detection where we try to find an axis 
// where the objects are separated is called the separating axis test. 
// If there is no separating axis, then the objects are colliding.
//
// SDL does have some built in collision detection functions 
// but we roll our own so we know how it works.
bool Lesson27::checkCollision(SDL_Rect *a, SDL_Rect *b) {
	// The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Calculate the top/bottom and left/right of each collison box.

	// Calculate the sides of rect A
	leftA = a->x;
	rightA = a->x + a->w;
	topA = a->y;
	bottomA = a->y + a->h;

	// Calculate the sides of rect B
	leftB = b->x;
	rightB = b->x + b->w;
	topB = b->y;
	bottomB = b->y + b->h;

	// Separating axis test
	
	// If any of the sides from A are outside of B
	if (bottomA <= topB) {
		return false;
	}

	if (topA >= bottomB) {
		return false;
	}

	if (rightA <= leftB) {
		return false;
	}

	if (leftA >= rightB) {
		return false;
	}

	// If none of the sides from A are outside B
	return true;
}


int Lesson27::main(int argc, char* args[]) {
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
			LDot dot(this);			// The dot that will be moving around on the screen

			// Define the postion and dimensions of the wall
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

				dot.move();		// Move the dot

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				dot.render();	// Render dot

				SDL_RenderPresent(gRenderer);	// Update screen
			}
		}
	}

	close();	// Free resources and close SDL

	return 0;
}

