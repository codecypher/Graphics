#include "Lesson11.h"

Lesson11::Lesson11() {
	gSpriteSheetTexture = new LTexture(this);
}

// Load the texture and then defines the clip rectangles 
// for the circle sprites if the texture loaded successfully.
bool  Lesson11::loadMedia() {
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!gSpriteSheetTexture->loadFromFile("img/dots.png")) {
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
	else {
		// Set top left sprite
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 100;
		gSpriteClips[0].h = 100;

		// Set top right sprite
		gSpriteClips[1].x = 100;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 100;
		gSpriteClips[1].h = 100;

		// Set bottom left sprite
		gSpriteClips[2].x = 0;
		gSpriteClips[2].y = 100;
		gSpriteClips[2].w = 100;
		gSpriteClips[2].h = 100;

		// Set bottom right sprite
		gSpriteClips[3].x = 100;
		gSpriteClips[3].y = 100;
		gSpriteClips[3].w = 100;
		gSpriteClips[3].h = 100;
	}

	return success;
}


void  Lesson11::close() {
	// Free loaded images
	gSpriteSheetTexture->free();

	// Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


// We render the same texture 4 times, but we are rendering 
// a different portion of the sprite sheet in different places on each call.
int  Lesson11::main(int argc, char* args[]) {
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

			// While application is running
			while (!quit) {
				// Handle events on queue (event/game loop)
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render top left sprite
				gSpriteSheetTexture->render(0, 0, &gSpriteClips[0]);

				// Render top right sprite
				gSpriteSheetTexture->render(ScreenWidth - gSpriteClips[1].w, 0, &gSpriteClips[1]);

				// Render bottom left sprite
				gSpriteSheetTexture->render(0, ScreenHeight - gSpriteClips[2].h, &gSpriteClips[2]);

				// Render bottom right sprite
				gSpriteSheetTexture->render(ScreenWidth - gSpriteClips[3].w, ScreenHeight - gSpriteClips[3].h, &gSpriteClips[3]);

				// Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}

