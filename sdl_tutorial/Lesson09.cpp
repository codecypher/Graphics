#include "Lesson09.h"

Lesson09 Lesson09::_instance;

Lesson09::Lesson09() {
}


bool Lesson09::init() {
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
			SDL_WINDOW_SHOWN);

		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				// Initialize renderer color (white opaque)
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


bool Lesson09::loadMedia(){
	bool success = true;	// Loading success flag

	// Load texture
	gTexture = loadTexture("img/viewport.png");
	if (gTexture == NULL) {
		printf("Failed to load texture image!\n");
		success = false;
	}

	// Nothing to load
	return success;
}


void Lesson09::close() {
	// Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	// Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


SDL_Texture* Lesson09::loadTexture(std::string path) {
	SDL_Texture* newTexture = NULL;		// pointer to the final texture

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}


int Lesson09::main(int argc, char* args[]) {
	// Startup SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		// Load media
		if (!loadMedia())
		{
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

				// Top left corner viewport
				SDL_Rect topLeftViewport;
				topLeftViewport.x = 0;
				topLeftViewport.y = 0;
				topLeftViewport.w = ScreenWidth / 2;
				topLeftViewport.h = ScreenHeight / 2;
				SDL_RenderSetViewport(gRenderer, &topLeftViewport);

				// Render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				// Top right viewport
				// We define the top right area and draw to it.
				SDL_Rect topRightViewport;
				topRightViewport.x = ScreenWidth / 2;
				topRightViewport.y = 0;
				topRightViewport.w = ScreenWidth / 2;
				topRightViewport.h = ScreenHeight / 2;
				SDL_RenderSetViewport(gRenderer, &topRightViewport);

				// Render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				// Bottom viewport
				SDL_Rect bottomViewport;
				bottomViewport.x = 0;
				bottomViewport.y = ScreenHeight / 2;
				bottomViewport.w = ScreenWidth;
				bottomViewport.h = ScreenHeight / 2;
				SDL_RenderSetViewport(gRenderer, &bottomViewport);
				
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);	// Render texture to screen				
				SDL_RenderPresent(gRenderer);						// Update screen
			}
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}


Lesson09* Lesson09::GetInstance() { return &Lesson09::_instance; }

//SDL_Renderer* App::GetRenderer() { return Renderer; }

//int App::GetWindowWidth() { return WindowWidth; }
//int App::GetWindowHeight() { return WindowHeight; }

