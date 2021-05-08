#include "Lesson18.h"


Lesson18::Lesson18() {
	gPressTexture = new LTexture(this);
	gUpTexture = new LTexture(this);
	gDownTexture = new LTexture(this);
	gLeftTexture = new LTexture(this);
	gRightTexture = new LTexture(this);
}

bool Lesson18::loadMedia() {
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


void Lesson18::close() {
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


// There are ways to get the state of the input devices (mouse, keyboard, etc) other than using events.
// We can redo the keyboard input tutorial using key states instead of events.
int Lesson18::main(int argc, char* args[]) {
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

				// The state of all the keys are ordered by SDL_Scancode.
				// Scan codes are like the SDL_Keycode values, but scan codes are designed to work with international keyboards.
				// Depending on the keyboard layout, different letters might be in different places.
				// Scan codes use default physical position of the keys rather than where they might be on a specific keyboard.

				// To check if a key is down, we simply check its state in the key state array.

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
