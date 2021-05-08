#include "Lesson03.h"

Lesson03 Lesson03::_instance;

Lesson03::Lesson03() {
}

bool Lesson03::init() {
	bool success = true;	// Initialization flag

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
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
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			gScreenSurface = SDL_GetWindowSurface(gWindow);  // Get window surface
		}
	}

	return success;
}

bool Lesson03::loadMedia() {
	bool success = true;	// Loading success flag

	// Load splash image
	gXOut = SDL_LoadBMP("img/x.bmp");
	if (gXOut == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "03_event_driven_programming/x.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void Lesson03::close() {
	// Deallocate surface
	SDL_FreeSurface(gXOut);
	gXOut = NULL;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

// SDL_Event is a union. 
// An SDL event is something like a key press, mouse motion, joy button press, etc. 
// In this application, we are going to look for quit events to end the application.
int Lesson03::main(int argc, char* args[]) {
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
			// Main loop flag
			bool quit = false;
			 
			// Event handler
			SDL_Event e;

			// While application is running
			while (!quit) {
				// Handle events on queue
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}

				// Apply the image
				SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);

				// Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}


Lesson03* Lesson03::GetInstance() { return &Lesson03::_instance; }

//SDL_Renderer* App::GetRenderer() { return Renderer; }

//int App::GetWindowWidth() { return WindowWidth; }
//int App::GetWindowHeight() { return WindowHeight; }
