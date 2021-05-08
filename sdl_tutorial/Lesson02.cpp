// Using SDL and standard IO
#include "Lesson02.h"

Lesson02 Lesson02::_instance;

Lesson02::Lesson02() {
}

bool Lesson02::init() {
	// Initialization flag
	bool success = true;

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
			SDL_WINDOW_SHOWN );
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			// Get window surface
			// We want to show images inside of the window 
			// so we need to get the image inside of the window. 
			// Thus, we need to grab the surface contained by the window.
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

// Load splash image
// The working directory is usually the directory where your executable is located, 
// but Visual Studio changes the working directory to where the vcxproj file is located.
bool Lesson02::loadMedia() {
	bool success = true;	// Loading success flag

	gHelloWorld = SDL_LoadBMP("img/hello_world.bmp");
	if (gHelloWorld == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", 
			   "02_getting_an_image_on_the_screen/hello_world.bmp", 
			   SDL_GetError());
		success = false;
	}

	return success;
}

// Cleanup resources
void Lesson02::close() {
	// Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

// Blit the loaded surface (image) onto the screen surface (window)
// 
// When you draw to the screen, you are not typically drawing to the image on the screen. 
// By default, most rendering systems are double-buffered: the front and back buffer.
//
// If we only had a front buffer, we would be able to see the frame as things are being drawn 
// so we would see unfinished frames. So we draw everything to the back buffer and 
// when we are done we swap the back and front buffer to show the user the finished frame.
int Lesson02::main(int argc, char* args[]) {
	// Start SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		// Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			// Apply the image (render to back buffer)
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
			
			// Update the surface (render to front buffer)
			SDL_UpdateWindowSurface(gWindow);

			// Wait two seconds
			SDL_Delay(2000);
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}


Lesson02* Lesson02::GetInstance() { return &Lesson02::_instance; }

//SDL_Renderer* App::GetRenderer() { return Renderer; }

//int App::GetWindowWidth() { return WindowWidth; }
//int App::GetWindowHeight() { return WindowHeight; }
