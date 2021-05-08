#include "Lesson10.h"

//Lesson10 Lesson10::_instance;

Lesson10::Lesson10() {
	//gFooTexture = new LTexture(this);
	//gBackgroundTexture = new LTexture(this);
}


bool Lesson10::init(){
	// Initialization flag
	bool success = true;

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


bool Lesson10::loadMedia() {
	bool success = true;	// Loading success flag
	
	// Load Foo texture
	if (!gFooTexture->loadFromFile("img/foo.png")) {
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	// Load background texture
	if (!gBackgroundTexture->loadFromFile("img/background.png")) {
		printf("Failed to load background texture image!\n");
		success = false;
	}

	return success;
}


void Lesson10::close() {
	// Free loaded images
	gFooTexture->free();
	gBackgroundTexture->free();

	// Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


// Note that order matters when rendering multiple things to the screen every frame. 
// If we render the stick figure first, the background will render over it 
// and we willn ot be able to see the stick figure.
int Lesson10::main(int argc, char* args[]) {
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
				// Handle events on queue
				while (SDL_PollEvent(&e) != 0) {
					//User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render background texture to screen
				gBackgroundTexture->render(0, 0);

				// Render Foo to the screen
				gFooTexture->render(240, 190);

				// Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}


//Lesson10* Lesson10::GetInstance() { return new Lesson10(); }

//Lesson10* Lesson10::GetInstance() { return &Lesson10::_instance; }

//SDL_Renderer* App::GetRenderer() { return Renderer; }

//int App::GetWindowWidth() { return WindowWidth; }
//int App::GetWindowHeight() { return WindowHeight; }

