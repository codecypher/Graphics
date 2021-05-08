#include "Lesson14.h"

Lesson14::Lesson14() {
	gSpriteSheetTexture = new LTexture(this);
}


bool Lesson14::loadMedia() {	
	bool success = true;	// Loading success flag

	// Load sprite sheet texture
	if (!gSpriteSheetTexture->loadFromFile("img/foo_sprite.png")) {
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else {
		// Set sprite clips
		// Define the sprites for the individual frames of animation.
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 64;
		gSpriteClips[0].h = 205;

		gSpriteClips[1].x = 64;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 64;
		gSpriteClips[1].h = 205;

		gSpriteClips[2].x = 128;
		gSpriteClips[2].y = 0;
		gSpriteClips[2].w = 64;
		gSpriteClips[2].h = 205;

		gSpriteClips[3].x = 196;
		gSpriteClips[3].y = 0;
		gSpriteClips[3].w = 64;
		gSpriteClips[3].h = 205;
	}

	return success;
}

void Lesson14::close() {
	// Free loaded images
	gSpriteSheetTexture->free();

	// Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int Lesson14::main(int argc, char* args[]) {
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
			int frame = 0;		// Current animation frame

			// While application is running
			while (!quit) {
				// Handle events on queue (event/game loop)
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render current frame
				// Since there are only 4 frames of animation, we want to slow down the animation a bit. 
				// We get the current clip sprite and divide the frame by 4 so that the actual frame 
				// of animation only updates every 4 frames since with int data types:
				// 0 / 4 = 0, 1 / 4 = 0, 2 / 4 = 0, 3 / 4 = 0, 4 / 4 = 1, 5 / 4 = 1, etc.
				SDL_Rect* currentClip = &gSpriteClips[frame / 4];
				gSpriteSheetTexture->render((ScreenWidth - currentClip->w) / 2, (ScreenHeight - currentClip->h) / 2, currentClip);

				// Update screen
				SDL_RenderPresent(gRenderer);
				
				// Go to next frame
				// For the frame to update, we need to increment the frame value every frame.
				++frame;

				// Cycle animation
				// e also want the animation to cycle, so when the frame hits the final value (16 / 4 = 4) 
				// we reset the frame to 0 so the animation starts over again.
				if (frame / 4 >= WALKING_ANIMATION_FRAMES) {
					frame = 0;
				}
			}
		}
	}
	
	close();	// Free resources and close SDL

	return 0;
}


Lesson14* Lesson14::GetInstance() { return new Lesson14(); }
