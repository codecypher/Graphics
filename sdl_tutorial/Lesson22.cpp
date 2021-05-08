#include "Lesson22.h"


Lesson22::Lesson22() {
	gTimeTextTexture = new LTexture(this);
	gPromptTextTexture = new LTexture(this);
}

bool Lesson22::init() {
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


// We want to minimize the amount of times that we render text. 
// We have a texture to prompt input and a texture to display the current time in milliseconds. 
// The time texture changes every frame so we have to render that every frame, 
// but the prompt texture  does not change so we can render it once in the file loading function.
bool Lesson22::loadMedia() {
	bool success = true;	// Loading success flag

	// Open the font
	gFont = TTF_OpenFont("img/lazy.ttf", 28);
	if (gFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		// Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };

		// Load prompt texture
		if (!gPromptTextTexture->loadFromRenderedText("Press Enter to Reset Start Time.", textColor)) {
			printf("Unable to render prompt texture!\n");
			success = false;
		}
	}

	return success;
}


void Lesson22::close() {
	// Free loaded images
	gTimeTextTexture->free();
	gPromptTextTexture->free();

	// Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	__super::close();

	// Quit SDL subsystems
	TTF_Quit();
}


int Lesson22::main(int argc, char* args[]) {
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
			bool quit = false;		// Main loop flag			
			SDL_Event e;			// Event handler

						
			SDL_Color textColor = { 0, 0, 0, 255 };		// Set text color as black

			Uint32 startTime = 0;			// Current time start time
	
			// in-memory text stream
			// instead of reading or writing to the console,  
			// string streams allow us to read and write to a string in memory.
			std::stringstream timeText;		

			// While application is running
			while (!quit) {
				// Handle events on queue (event/game queue)
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					// Reset start time when user presses return
					else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
						startTime = SDL_GetTicks();
					}
				}

				// Set text to be rendered
				timeText.str("");
				timeText << "Milliseconds since start time " << SDL_GetTicks() - startTime;

				// Render text to texture
				if (!gTimeTextTexture->loadFromRenderedText(timeText.str().c_str(), textColor)) {
					printf("Unable to render time texture!\n");
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render textures
				gPromptTextTexture->render((ScreenWidth - gPromptTextTexture->getWidth()) / 2, 0);
				gTimeTextTexture->render(
					(ScreenWidth - gPromptTextTexture->getWidth()) / 2,
					(ScreenHeight - gPromptTextTexture->getHeight()) / 2);

				// Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();	// Free resources and close SDL

	return 0;
}

