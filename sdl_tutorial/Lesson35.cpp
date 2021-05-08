#include <stdio.h>
#include <string>
#include <sstream>

#include "Lesson35.h"

Lesson35::Lesson35() {
	gSceneTexture = new LTexture(this);
	gWindow = new LWindow(this);
}

bool Lesson35::init() {	
	bool success = true;	// Initialization flag

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		if (!gWindow->init()) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			// Create renderer for window
			gRenderer = gWindow->createRenderer();
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}


bool Lesson35::loadMedia() {
	//Loading success flag
	bool success = true;

	//Load scene texture
	if (!gSceneTexture->loadFromFile("img/window.png")) {
		printf("Failed to load window texture!\n");
		success = false;
	}

	return success;
}

void Lesson35::close() {
	// Free loaded images
	gSceneTexture->free();

	// Destroy window	
	SDL_DestroyRenderer(gRenderer);
	gWindow->free();

	__super::close();
}

int Lesson35::main(int argc, char* args[]) {
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
			bool quit = false;	// Main loop flag
			SDL_Event e;		// Event handler

			// Text rendering color
			SDL_Color textColor = { 0, 0, 0, 0xFF };
			SDL_Color highlightColor = { 0xFF, 0, 0, 0xFF };

			// Current input point
			// Keep track of which of our data integers we are altering
			int currentData = 0;

			// While application is running
			while (!quit) {
				// Handle events on queue (event/game queue)
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}

					// Pass events to the window wrapper to handle window events
					gWindow->handleEvent(e);
				}

				// Only draw when not minimized
				if (!gWindow->isMinimized()) {
					// Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);

					// Render text textures
					gSceneTexture->render((gWindow->getWidth() - gSceneTexture->getWidth()) / 2,
										 (gWindow->getHeight() - gSceneTexture->getHeight()) / 2);

					// Update screen
					SDL_RenderPresent(gRenderer);
				}
			}
		}
	}
	
	close();	// Free resources and close SDL

	return 0;

}

