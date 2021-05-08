#include "Lesson08.h"

Lesson08 Lesson08::_instance;

Lesson08::Lesson08() {
}


bool Lesson08::init() {
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


// SDL primitive rendering allows you to render shapes 
// without loading special graphics.
bool Lesson08::loadMedia() {
	bool success = true;	// Loading success flag
	return success;			// Nothing to load
}


void Lesson08::close() {
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


SDL_Texture* Lesson08::loadTexture(std::string path) {
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


// Notice that making the y coordinate larger makes it go down and 
// making the y coordinate smaller makes it go up
// because SDL and many 2D rendering APIs use a different coordinate system.
int Lesson08::main(int argc, char* args[]) {
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
				// Set the clearing color to white: RGBA (red, green, blue, alpha)
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);  
				SDL_RenderClear(gRenderer);

				// Render red filled quad (x, y, width, height)
				SDL_Rect fillRect = { ScreenWidth / 4, ScreenHeight / 4, ScreenWidth / 2, ScreenHeight / 2 };
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);  // set color to opaque red
				SDL_RenderFillRect(gRenderer, &fillRect);  // draw the rectangle

				// Render green outlined quad
				SDL_Rect outlineRect = { ScreenWidth / 6, ScreenHeight / 6, ScreenWidth * 2 / 3, ScreenHeight * 2 / 3 };
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
				SDL_RenderDrawRect(gRenderer, &outlineRect);

				// Draw blue horizontal line
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
				SDL_RenderDrawLine(gRenderer, 0, ScreenHeight / 2, ScreenWidth, ScreenHeight / 2);

				// Draw vertical line of yellow dots (a sequence of dots)
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
				for (int i = 0; i < ScreenHeight; i += 4) {
					SDL_RenderDrawPoint(gRenderer, ScreenWidth / 2, i);
				}

				// Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}


Lesson08* Lesson08::GetInstance() { return &Lesson08::_instance; }

//SDL_Renderer* App::GetRenderer() { return Renderer; }

//int App::GetWindowWidth() { return WindowWidth; }
//int App::GetWindowHeight() { return WindowHeight; }

