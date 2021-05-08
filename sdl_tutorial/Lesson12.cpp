#include "Lesson12.h"

Lesson12::Lesson12() {
	gModulatedTexture = new LTexture(this);
}

bool Lesson12::loadMedia() {
	bool success = true;	// Loading success flag

	// Load texture
	if (!gModulatedTexture->loadFromFile("img/colors.png")) {
		printf("Failed to load colors texture!\n");
		success = false;
	}

	return success;
}

void Lesson12::close() {
	// Free loaded images
	gModulatedTexture->free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int Lesson12::main(int argc, char* args[]) {
	//Start up SDL and create window
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

			// Modulation components
			Uint8 r = 255;
			Uint8 g = 255;
			Uint8 b = 255;

			// While application is running
			while (!quit) {
				// Handle events on queue
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					// On keypress change rgb values
					else if (e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym) {
							// increase red
							case SDLK_q:
								r += 32;
								break;
							// increase green
							case SDLK_w:
								g += 32;
								break;
							// increase blue
							case SDLK_e:
								b += 32;
								break;
							// decrease red
							case SDLK_a:
								r -= 32;
								break;
							// decrease green
							case SDLK_s:
								g -= 32;
								break;
							// decrease blue
							case SDLK_d:
								b -= 32;
								break;
						}
					}
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Modulate and render texture
				gModulatedTexture->setColor(r, g, b);
				gModulatedTexture->render(0, 0);

				// Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}
