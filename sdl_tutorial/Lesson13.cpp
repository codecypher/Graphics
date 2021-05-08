#include "Lesson13.h"

Lesson13::Lesson13() {
	gModulatedTexture = new LTexture(this);
	gBackgroundTexture = new LTexture(this);
}


// Load the front texture that we are going to alpha blend and a background texture. 
// As the front texture gets more transparent, we can see more of the background texture.
//
// Alpha is opacity and the lower the opacity the more we can see through it. 
// Like red, green, or blue color components it goes from 0 to 255 when modulating it.
// The lower the alpha value, the more transparent it is.
bool Lesson13::loadMedia() {
	bool success = true;	// Loading success flag

	// Load front alpha texture
	if (!gModulatedTexture->loadFromFile("img/fadeout.png")) {
		printf("Failed to load front texture!\n");
		success = false;
	}
	else {
		// Set standard alpha blending (enable blending)
		gModulatedTexture->setBlendMode(SDL_BLENDMODE_BLEND);
	}

	// Load background texture
	if (!gBackgroundTexture->loadFromFile("img/fadein.png")) {
		printf("Failed to load background texture!\n");
		success = false;
	}

	return success;
}

void Lesson13::close() {
	// Free loaded images
	gModulatedTexture->free();
	gBackgroundTexture->free();

	// estroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


// After clearing the screen we render the background first 
// then we render the front modulated texture over it. 
// Right before rendering the front texture, we set the alpha value. 
int Lesson13::main(int argc, char* args[]) {
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
			
			bool quit = false;	// Main loop flag			
			SDL_Event e;		// Event handler			
			Uint8 a = 255;		// Modulation component

			// While application is running
			while (!quit) {
				// Handle events on queue (event/game loop)
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					// Handle key presses
					else if (e.type == SDL_KEYDOWN) {
						// Increase alpha on w
						if (e.key.keysym.sym == SDLK_w) {
							// Cap if over 255
							if (a + 32 > 255) {
								a = 255;
							}
							// Increment otherwise
							else {
								a += 32;
							}
						}
						// Decrease alpha on s
						else if (e.key.keysym.sym == SDLK_s) {
							// Cap if below 0
							if (a - 32 < 0) {
								a = 0;
							}
							// Decrement otherwise
							else {
								a -= 32;
							}
						}
					}
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render background
				gBackgroundTexture->render(0, 0);

				// Render front blended
				gModulatedTexture->setAlpha(a);
				gModulatedTexture->render(0, 0);

				// Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

