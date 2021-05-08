#include "framework.h"
#include "AppSDL.hpp"
#include "AppGL.hpp"

AppSDL::AppSDL() {
}


bool AppSDL::init() {
	bool success = true;	// Initialization flag

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow(
			"SDL Tutorial",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			ScreenWidth,
			ScreenHeight,
			SDL_WINDOW_HIDDEN);

		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			// Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				//int imgFlags = IMG_INIT_PNG;
				//if (!(IMG_Init(imgFlags) & imgFlags)) {
				//	printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				//	success = false;
				//}
			}
		}
	}

	return success;
}


// Load all the images that we are going to render to the screen.
bool AppSDL::loadMedia() {
	bool success = true;	// Loading success flag
	return success;
}


void AppSDL::close() {
	// Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	//IMG_Quit();
	SDL_Quit();
}


int AppSDL::main_sdl(int argc, char* args[]) {
	// Load media
	if (!loadMedia()) {
		printf("Failed to load media!\n");
	}
	else {
		bool quit = false;					// Main loop flag
		SDL_Event e;						// Event handler
		//LTexture* currentTexture = NULL;	// pointer to current rendered texture

		// While SDL application is running
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

			// Render current texture
			//currentTexture->render(0, 0);

			// Update screen
			SDL_RenderPresent(gRenderer);
		}
	}
	
	return 0;
}

int AppSDL::main(int argc, char* args[]) {
	// Startup SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		//main_sdl(argc, args);
		AppGL* pGL = new AppGL();
		pGL->main_gl(argc, args);
	}

	close();	// Free resources and close SDL

	return 0;
}

