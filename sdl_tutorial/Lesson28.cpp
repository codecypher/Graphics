#include "Lesson28.h"


Lesson28::Lesson28() {
	gDotTexture = new LTexture(this);
}


// We want to minimize the amount of times that we render text. 
bool Lesson28::loadMedia() {
	bool success = true;	// Loading success flag

	// Load dot texture
	if (!gDotTexture->loadFromFile("img/dot.bmp")) {
		printf("Failed to load dot texture!\n");
		success = false;
	}

	return success;
}


void Lesson28::close() {
	// Free loaded images
	gDotTexture->free();

	__super::close();
}



bool Lesson28::checkPixelCollision(std::vector<SDL_Rect> &a, std::vector<SDL_Rect> &b) {
	// The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Go through the A boxes
	// Calculate the top/bottom/left/right of each collision box in object A.
	for (int Abox = 0; Abox < a.size(); Abox++) {
		// Calculate the sides of rect A
		leftA = a[Abox].x;
		rightA = a[Abox].x + a[Abox].w;
		topA = a[Abox].y;
		bottomA = a[Abox].y + a[Abox].h;

		// Go through the B boxes
		// Calculate the top/bottom/left/right of each collision box in object B.
		for (int Bbox = 0; Bbox < b.size(); Bbox++) {
			// Calculate the sides of rect B
			leftB = b[Bbox].x;
			rightB = b[Bbox].x + b[Bbox].w;
			topB = b[Bbox].y;
			bottomB = b[Bbox].y + b[Bbox].h;

			// If no sides from A are outside of B
			// Check if there is no separating axis?
			if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false) {
				// A collision is detected
				return true;
			}
		}
	}

	// If neither set of collision boxes touched
	return false;
}



int Lesson28::main(int argc, char* args[]) {
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
			LDot dot(0, 0, this);

			// The dot that will be collided against
			LDot otherDot(ScreenWidth / 4, ScreenHeight / 4, this);

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
				dot.move(otherDot.getColliders());

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render dots
				dot.render();	
				otherDot.render();

				SDL_RenderPresent(gRenderer);	// Update screen
			}
		}
	}

	close();	// Free resources and close SDL

	return 0;
}

