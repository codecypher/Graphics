#include "Lesson05.h"

Lesson05 Lesson05::_instance;

Lesson05::Lesson05() {
}


bool Lesson05::init() {
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		// Create window
		gWindow = SDL_CreateWindow(
				"SDL Tutorial", 
				SDL_WINDOWPOS_UNDEFINED, 
				SDL_WINDOWPOS_UNDEFINED, 
				ScreenWidth, 
				ScreenHeight, 
				SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}


bool Lesson05::loadMedia() {
	bool success = true;	// Loading success flag

	// Load stretching surface
	gStretchedSurface = loadSurface("img/stretch.bmp");
	if (gStretchedSurface == NULL) {
		printf("Failed to load stretching image!\n");
		success = false;
	}

	return success;
}


void Lesson05::close() {
	// Free loaded image
	SDL_FreeSurface(gStretchedSurface);
	gStretchedSurface = NULL;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}


// When we load a bitmap, it is usually loaded in a 24-bit format (most bitmaps are 24-bit). 
// Most modern displays are not 24-bit so if we blit an image that is 24-bit onto a 32-bit image, 
// SDL will convert it every time the image is blitted.
//
// So when an image is loaded we convert it to the same format as the screen 
// so that no conversion needs to be done on blit which can be done easily with SDL_ConvertSurface. 
// All we have to do is pass in the surface we want to convert with the format of the screen.
SDL_Surface* Lesson05::loadSurface(std::string path) {
	SDL_Surface* optimizedSurface = NULL;	// pointer to the final optimized image

	// Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else {
		// Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (optimizedSurface == NULL) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		// Get rid of old loaded surface
		// SDL_ConvertSurface returns a copy of the original in a new format, 
		// so the original loaded image is still in memory which means that 
		// we have to free the original loaded surface or we will have two copies 
		// of the same image in memory.
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;  // we return the final optimized image
}


// So far we been blitting our images raw.
// When you're making a game, blitting images raw can cause needless slow down.
// We convert them to an optimized format to speed them up.
//
// SDL 2 also has a new feature for SDL surfaces called soft stretching
// that allows you to blit an image scaled to a different size.
// In this tutorial we take an image half the size of the screen and stretch it to the full size.
int Lesson05::main(int argc, char* args[]) {
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

				// Apply the image stretched
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = ScreenWidth;
				stretchRect.h = ScreenHeight;
				SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);

				// Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}


Lesson05* Lesson05::GetInstance() { return &Lesson05::_instance; }

//SDL_Renderer* App::GetRenderer() { return Renderer; }

//int App::GetWindowWidth() { return WindowWidth; }
//int App::GetWindowHeight() { return WindowHeight; }
