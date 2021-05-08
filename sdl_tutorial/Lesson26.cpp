#include "Lesson26.h"


Lesson26::Lesson26() {
	gDotTexture = new LTexture(this);
}


// We want to minimize the amount of times that we render text. 
bool Lesson26::loadMedia() {
	bool success = true;	// Loading success flag

	// Load dot texture
	if (!gDotTexture->loadFromFile("img/dot.bmp")) {
		printf("Failed to load dot texture!\n");
		success = false;
	}

	return success;
}


void Lesson26::close() {
	// Free loaded images
	gDotTexture->free();

	__super::close();
}


int Lesson26::main(int argc, char* args[]) {
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

				dot.render();	// Render objects
				
				SDL_RenderPresent(gRenderer);	// Update screen
			}
		}
	}

	close();	// Free resources and close SDL

	return 0;
}

