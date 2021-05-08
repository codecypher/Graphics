#include "Lesson17.h"

LButton::LButton() {
	// initialize the default sprite and set position.
	mPosition.x = 0;
	mPosition.y = 0;
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

LButton::LButton(Lesson17* ptr) {
	mPosition.x = 0;
	mPosition.y = 0;
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	root = ptr;
}

void LButton::setPosition(int x, int y) {
	mPosition.x = x;
	mPosition.y = y;
}


// Handle the mouse events
// This function will be called in the event loop and will handle an event 
// taken from the event queue for an individual button.
// We display different sprites depeding on the mouse event.
//
// The origin of the button is at the top left.
// This means every x coordinate less than the x position is outside of the button 
// and every y coordinate less than the y position is too. 
// Everything right of the button is the x position + the width 
// and everything below the button is the y position + the height.
void LButton::handleEvent(SDL_Event* e) {
	// Check if the event is a mouse event
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Check if mouse is in button
		bool inside = true;

		// Assume mouse is in button.
		// If the mouse position is in any way outside
		// the button then inside is set to false.
		
		// Mouse is left of the button
		if (x < mPosition.x) {
			inside = false;
		}
		// Mouse is right of the button
		else if (x > mPosition.x + BUTTON_WIDTH) {
			inside = false;
		}
		// Mouse above the button
		else if (y < mPosition.y) {
			inside = false;
		}
		// Mouse below the button
		else if (y > mPosition.y + BUTTON_HEIGHT) {
			inside = false;
		}

		// Mouse is outside button
		if (!inside) {
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		// Mouse is inside button
		else {
			// Set mouse over sprite
			switch (e->type) {
				case SDL_MOUSEMOTION:
					mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
					break;
				case SDL_MOUSEBUTTONDOWN:
					mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
					break;
				case SDL_MOUSEBUTTONUP:
					mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
					break;
			}
		}
	}
}

// Show current button sprite
// Render the current button sprite at the button position.
void LButton::render() {
	root->gButtonSpriteSheetTexture->render(mPosition.x, mPosition.y, &root->gSpriteClips[mCurrentSprite]);
}


Lesson17::Lesson17() {
	gButtonSpriteSheetTexture = new LTexture(this);

	// Dynamically allocate each Button
	for (int i = 0; i < NUM_BUTTONS; i++) {
		gButtons[i] = new LButton(this);
	}
}


bool Lesson17::loadMedia() {
	bool success = true;	// Loading success flag

	//Load sprites
	if (!gButtonSpriteSheetTexture->loadFromFile("img/button.png")) {
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else {
		// Set sprites
		for (int i = 0; i < NUM_BUTTONS; ++i) {
			gSpriteClips[i].x = 0;
			gSpriteClips[i].y = i * 200;
			gSpriteClips[i].w = BUTTON_WIDTH;
			gSpriteClips[i].h = BUTTON_HEIGHT;
		}

		// Set buttons in corners
		gButtons[0]->setPosition(0, 0);
		gButtons[1]->setPosition(ScreenWidth - BUTTON_WIDTH, 0);
		gButtons[2]->setPosition(0, ScreenHeight - BUTTON_HEIGHT);
		gButtons[3]->setPosition(ScreenWidth - BUTTON_WIDTH, ScreenHeight - BUTTON_HEIGHT);
	}


	return success;
}

void Lesson17::close() {
	// Free loaded images
	gButtonSpriteSheetTexture->free();

	// Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int Lesson17::main(int argc, char* args[]) {
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
			bool quit = false;		// Main loop flag			
			SDL_Event e;			// Event handler

			// While application is running
			while (!quit) {
				// Handle events on queue (event/game queue)
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}

					// Handle button events
					for (int i = 0; i < NUM_BUTTONS; ++i) {
						gButtons[i]->handleEvent(&e);
					}
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render buttons
				for (int i = 0; i < NUM_BUTTONS; ++i) {
					gButtons[i]->render();
				}

				// Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();	// Free resources and close SDL

	return 0;
}

