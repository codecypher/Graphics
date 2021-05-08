#include "Lesson24.h"


Lesson24::Lesson24() {
	gFPSTextTexture = new LTexture(this);
}


// We want to minimize the amount of times that we render text.
bool Lesson24::loadMedia() {
	bool success = true;	// Loading success flag

	// Open the font
	gFont = TTF_OpenFont("img/lazy.ttf", 28);
	if (gFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	return success;
}


void Lesson24::close() {
	// Free loaded images
	gFPSTextTexture->free();

	__super::close();
}


int Lesson24::main(int argc, char* args[]) {
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

			LTimer fpsTimer;		// the frames per second timer

			// Start counting frames per second
			int countedFrames = 0;
			fpsTimer.start();

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
				}

				// Calculate and correct fps
				float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				if (avgFPS > 2000000) {
					avgFPS = 0;
				}

				// Set text to be rendered
				timeText.str("");
				timeText << "Average Frames Per Second " << avgFPS;

				// Render text to texture
				if (!gFPSTextTexture->loadFromRenderedText(timeText.str().c_str(), textColor)) {
					printf("Unable to render time texture!\n");
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render textures
				gFPSTextTexture->render((ScreenWidth - gFPSTextTexture->getWidth()) / 2, (ScreenHeight - gFPSTextTexture->getHeight()) / 2);

				// Update screen
				SDL_RenderPresent(gRenderer);
				++countedFrames;
			}
		}
	}

	close();	// Free resources and close SDL

	return 0;
}

