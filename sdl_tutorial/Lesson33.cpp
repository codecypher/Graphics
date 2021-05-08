#include <stdio.h>
#include <string>
#include <sstream>

#include "Lesson33.h"

Lesson33::Lesson33() {
	gPromptTextTexture = new LTexture(this);

	for (int i = 0; i < TOTAL_DATA; i++) {
		gDataTextures[i] = new LTexture(this);
	}

	for (int i = 0; i < TOTAL_DATA; i++) {
		gData[i] = new Sint32(0);
	}
}


// In our media loading function we are opening the save file for reading using SDL_RWFromFile. 
// The first argument is the path to the file and the second argument defines how we will be opening it. 
// r+b means it is being opened for reading in binary.
bool Lesson33::loadMedia() {
	// Text rendering color
	SDL_Color textColor = { 0, 0, 0, 0xFF };
	SDL_Color highlightColor = { 0xFF, 0, 0, 0xFF };
	
	bool success = true;  // Loading success flag

	// Open the font
	gFont = TTF_OpenFont("fonts/lazy.ttf", 28);
	if (gFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		// Render the prompt
		if (!gPromptTextTexture->loadFromRenderedText("Enter Data:", textColor)) {
			printf("Failed to render prompt text!\n");
			success = false;
		}
	}

	// Open file for reading in binary
	SDL_RWops* file = SDL_RWFromFile("data/nums.bin", "r+b");

	// File does not exist
	if (file == NULL) {
		printf("Warning: Unable to open file! SDL Error: %s\n", SDL_GetError());

		// Create file for writing
		file = SDL_RWFromFile("data/nums.bin", "w+b");
		if (file != NULL) {
			printf("New file created!\n");

			// Initialize data
			for (int i = 0; i < TOTAL_DATA; ++i) {
				*gData[i] = 0;
				Sint32 x = 0;
				SDL_RWwrite(file, &x, sizeof(Sint32), 1);
			}

			// Close file handler
			SDL_RWclose(file);
		}
		else {
			printf("Error: Unable to create file! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
	}
	// File exists
	else {
		// Load data
		printf("Reading file...!\n");
		for (int i = 0; i < TOTAL_DATA; ++i) {
			Sint32 x;
			SDL_RWread(file, &x, sizeof(Sint32), 1);
			*gData[i] = x;
		}

		// Close file handler
		SDL_RWclose(file);
	}

	// Initialize data textures
	// Render the text textures that correspond with each of our data numbers.
	int x0 = *gData[0];
	std::string s0 = std::to_string(x0);
	gDataTextures[0]->loadFromRenderedText(s0, highlightColor);
	for (int i = 1; i < TOTAL_DATA; ++i) {
		// Our loadFromRenderedText function only accepts strings 
		// so we have to convert the integers to strings.
		int x = *gData[i];
		std::string s = std::to_string(x);
		gDataTextures[i]->loadFromRenderedText(s, textColor);
	}

	return success;
}

void Lesson33::close() {
	// Open data for writing
	SDL_RWops* file = SDL_RWFromFile("data/nums.bin", "w+b");
	if (file != NULL) {
		//Save data
		for (int i = 0; i < TOTAL_DATA; ++i) {
			SDL_RWwrite(file, gData[i], sizeof(Sint32), 1);
		}

		// Close file handler
		SDL_RWclose(file);
	}
	else {
		printf("Error: Unable to save file! %s\n", SDL_GetError());
	}

	// Free loaded images
	gPromptTextTexture->free();
	for (int i = 0; i < TOTAL_DATA; ++i) {
		gDataTextures[i]->free();
	}

	__super::close();
}

int Lesson33::main(int argc, char* args[]) {
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
			bool quit = false;	// Main loop flag
			SDL_Event e;		// Event handler

			// Text rendering color
			SDL_Color textColor = { 0, 0, 0, 0xFF };
			SDL_Color highlightColor = { 0xFF, 0, 0, 0xFF };

			// Current input point
			// Keep track of which of our data integers we are altering
			int currentData = 0;

			// While application is running
			while (!quit) {
				// Handle events on queue (event/game queue)
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN) {
						Sint32 x = *gData[currentData];
						switch (e.key.keysym.sym) {
							// Previous data entry
							// When we press up or down we want to rerender the the old current data in plain color, 
							// move to the next data point (with some bounds checking), and rerender the new current data 
							// in the highlight color.
							case SDLK_UP:
								// Rerender previous entry input point
								x = *gData[currentData];
								gDataTextures[currentData]->loadFromRenderedText(std::to_string(x), textColor);
								--currentData;
								if (currentData < 0) {
									currentData = TOTAL_DATA - 1;
								}

								// Rerender current entry input point
								x = *gData[currentData];
								gDataTextures[currentData]->loadFromRenderedText(std::to_string(x), highlightColor);
								break;
							// Next data entry
							case SDLK_DOWN:
								// Rerender previous entry input point
								x = *gData[currentData];
								gDataTextures[currentData]->loadFromRenderedText(std::to_string(x), textColor);
								++currentData;
								if (currentData == TOTAL_DATA) {
									currentData = 0;
								}

								// Rerender current entry input point
								x = *gData[currentData];
								gDataTextures[currentData]->loadFromRenderedText(std::to_string(x), highlightColor);
								break;
							// Decrement input point
							// When we press left or right we decrement or increment the current data 
							// and rerender the texture associated with it.
							case SDLK_LEFT:
								//--gData[currentData];
								x = *gData[currentData];
								x++;
								*gData[currentData] = x;
								gDataTextures[currentData]->loadFromRenderedText(std::to_string(x), highlightColor);
								break;
							// Increment input point
							case SDLK_RIGHT:
								//++gData[currentData];
								x = *gData[currentData];
								x++;
								*gData[currentData] = x;
								gDataTextures[currentData]->loadFromRenderedText(std::to_string(x), highlightColor);
								break;
						}
					}
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render all the textures (text) to the screen
				gPromptTextTexture->render((ScreenWidth - gPromptTextTexture->getWidth()) / 2, 0);
				for (int i = 0; i < TOTAL_DATA; ++i) {
					gDataTextures[i]->render((ScreenWidth - gDataTextures[i]->getWidth()) / 2,
										      gPromptTextTexture->getHeight() + gDataTextures[0]->getHeight() * i);
				}
				
				SDL_RenderPresent(gRenderer);	// Update screen
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;

}

