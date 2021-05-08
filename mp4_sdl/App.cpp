#include "App.h"

App::App() {
	gPressTexture = new LTexture(this);
	gUpTexture = new LTexture(this);
	gDownTexture = new LTexture(this);
	gLeftTexture = new LTexture(this);
	gRightTexture = new LTexture(this);
}


bool App::init() {
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
			}
		}
	}

	return success;
}


// Load all the images that we are going to render to the screen.
// We have an array of surfaces for the images that correspond to a keypress (left, right, up, down).
// bool Lesson18::loadMedia() {
bool App::loadMedia() {
	bool success = true;	// Loading success flag

	// Load press texture
	if (!gPressTexture->loadFromFile("img/press.png")) {
		printf("Failed to load press texture!\n");
		success = false;
	}

	// Load up texture
	if (!gUpTexture->loadFromFile("img/up.png")) {
		printf("Failed to load up texture!\n");
		success = false;
	}

	// Load down texture
	if (!gDownTexture->loadFromFile("img/down.png")) {
		printf("Failed to load down texture!\n");
		success = false;
	}

	// Load left texture
	if (!gLeftTexture->loadFromFile("img/left.png")) {
		printf("Failed to load left texture!\n");
		success = false;
	}

	// Load right texture
	if (!gRightTexture->loadFromFile("img/right.png")) {
		printf("Failed to load right texture!\n");
		success = false;
	}

	return success;
}


void App::close() {
	// Free loaded images
	gPressTexture->free();
	gUpTexture->free();
	gDownTexture->free();
	gLeftTexture->free();
	gRightTexture->free();

	// Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int App::main(int argc, char* args[]) {
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
			bool quit = false;					// Main loop flag
			SDL_Event e;						// Event handler
			LTexture* currentTexture = NULL;	// pointer to current rendered texture

			// While application is running
			while (!quit) {
				// Handle events on queue (event/game loop)
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}

				// Set texture based on current keystate
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if (currentKeyStates[SDL_SCANCODE_UP]) {
					currentTexture = gUpTexture;
				}
				else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
					currentTexture = gDownTexture;
				}
				else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
					currentTexture = gLeftTexture;
				}
				else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
					currentTexture = gRightTexture;
				}
				else {  // none of the keys are down
					currentTexture = gPressTexture;
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render current texture
				currentTexture->render(0, 0);

				// Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	
	close();	// Free resources and close SDL

	return 0;
}


//App* App::GetInstance() { return &App::_instance; }

//SDL_Renderer* App::GetRenderer() { return Renderer; }

//int App::GetWindowWidth() { return WindowWidth; }
//int App::GetWindowHeight() { return WindowHeight; }
