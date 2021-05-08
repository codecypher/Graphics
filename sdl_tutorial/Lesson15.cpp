#include "Lesson15.h"

Lesson15::Lesson15() {
	gArrowTexture = new LTexture(this);
}

bool Lesson15::loadMedia() {
	bool success = true;	// Loading success flag

	// Load sprite texture
	if (!gArrowTexture->loadFromFile("img/arrow.png")) {
		printf("Failed to load walking animation texture!\n");
		success = false;
	}

	return success;
}

void Lesson15::close() {
	// Free loaded images
	gArrowTexture->free();

	// Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int Lesson15::main(int argc, char* args[]) {
	// Start up SDL and create window
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
			double degrees = 0;		// Angle of rotation

			// Flip type
			SDL_RendererFlip flipType = SDL_FLIP_NONE;

			// While application is running
			while (!quit) {
				// Handle events on queue (event/game queue)
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym) {
							case SDLK_a:
								degrees -= 60;
								break;

							case SDLK_d:
								degrees += 60;
								break;

							case SDLK_q:
								flipType = SDL_FLIP_HORIZONTAL;
								break;

							case SDLK_w:
								flipType = SDL_FLIP_NONE;
								break;

							case SDLK_e:
								flipType = SDL_FLIP_VERTICAL;
								break;
						}
					}
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render arrow
				// It may look like a complicated equation, but all it does is center the image.
				// First we pass in the x and y coordinates. 
				// The next argument is the clip rectangle, but we are rendering the whole texture so we set it to null.
				// The next argument is the rotation angle in degrees.
				// The next argument is the point we are rotating around. If null, it will rotate around the center of the image. 
				// The last argument is how the image is flipped.
				gArrowTexture->render((ScreenWidth - gArrowTexture->getWidth()) / 2,
					(ScreenHeight - gArrowTexture->getHeight()) / 2,
					NULL, 
					degrees,
					NULL, 
					flipType);

				// Update screen
				SDL_RenderPresent(gRenderer);
			}

		}
	}

	close();	// Free resources and close SDL

	return 0;
}


