#include "Lesson30.h"

Lesson30::Lesson30() {
	gDotTexture = new LTexture(this);
	gBGTexture = new LTexture(this);
}


bool Lesson30::loadMedia() {
	bool success = true;	// Loading success flag

	// Load dot texture
	if (!gDotTexture->loadFromFile("img/dot.bmp")) {
		printf("Failed to load dot texture!\n");
		success = false;
	}

	// Load background texture
	if (!gBGTexture->loadFromFile("img/bg.png")) {
		printf("Failed to load background texture!\n");
		success = false;
	}

	return success;
}


void Lesson30::close() {
	// Free loaded images
	gDotTexture->free();
	gBGTexture->free();
	__super::close();
}

int Lesson30::main(int argc, char* args[]) {
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

			// The dot that will be moving around on the screen
			LDot dot(this);

			// The camera area
			SDL_Rect camera = { 0, 0, ScreenWidth, ScreenHeight };

			// While application is running
			while (!quit) {
				// Handle events on queue (event/game queue)
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}

					dot.handleEvent(e);		// Handle input for the dot
				}

				// Move the dot
				dot.move_scroll();

				// Center the camera over the dot
				camera.x = (dot.getPosX() + LDot::DOT_WIDTH / 2) - ScreenWidth / 2;
				camera.y = (dot.getPosY() + LDot::DOT_HEIGHT / 2) - ScreenHeight / 2;

				// Keep the camera in bounds
				if (camera.x < 0) {
					camera.x = 0;
				}
				if (camera.y < 0) {
					camera.y = 0;
				}
				if (camera.x > LEVEL_WIDTH - camera.w) {
					camera.x = LEVEL_WIDTH - camera.w;
				}
				if (camera.y > LEVEL_HEIGHT - camera.h) {
					camera.y = LEVEL_HEIGHT - camera.h;
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				
				gBGTexture->render(0, 0, &camera);	// Render background	
				dot.render(camera.x, camera.y);		// Render objects

				SDL_RenderPresent(gRenderer);	// Update screen
			}
		}
	}

	close();	// Free resources and close SDL

	return 0;
}

