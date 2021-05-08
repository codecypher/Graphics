#include "Lesson.h"

// Lesson Lesson::_instance;

Lesson::Lesson() {
	//gTextTexture = new LTexture(this);
}


bool Lesson::init() {
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
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				// Initialize SDL_ttf
				if (TTF_Init() == -1) {
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}


// SDL primitive rendering allows you to render shapes 
// without loading special graphics.
bool Lesson::loadMedia() {
	bool success = true;	// Loading success flag
	return success;			// Nothing to load
}


void Lesson::close() {
	// Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	// Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


// Lesson 27: Collision Detection
bool Lesson::checkCollision(SDL_Rect *a, SDL_Rect *b) {
	return false;	
}

// Lesson 28: Per-pixel Collision Detection
// Checks sets of collision boxes against each other.
bool Lesson::checkPixelCollision(std::vector<SDL_Rect> &a, std::vector<SDL_Rect> &b) {
	return false;
}

// Lesson 29: Circular Collision Detection
// Circle/Circle collision detector
bool Lesson::checkCollision(LCircle& a, LCircle& b) {
	return false;
}

// Circle/Box collision detector
bool Lesson::checkCollision(LCircle& a, SDL_Rect& b) {
	return false;
}

// Calculate distance squared between two points
double Lesson::distanceSquared(int x1, int y1, int x2, int y2) {
	return 0;
}


int Lesson::main(int argc, char* args[]) {
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

			// While application is running
			while (!quit) {
				// Handle events on queue (event/game queue)
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Update screen
				SDL_RenderPresent(gRenderer);
			}

		}
	}

	close();	// Free resources and close SDL

	return 0;
}


//Lesson* Lesson::GetInstance() { return new Lesson(); }

