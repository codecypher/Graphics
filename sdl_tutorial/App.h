#pragma once

#ifndef _APP_H_
#define _APP_H_

#include <SDL2/SDL.h>
#include "TextureBank.h"

class App {
private:
	static App Instance;

	bool Running = true;

	SDL_Window* Window = NULL;
	SDL_Renderer* Renderer = NULL;
	SDL_Surface* PrimarySurface = NULL;

	static const int WindowWidth = 1024;
	static const int WindowHeight = 768;

	Texture* TestTexture;

private:
	App();

	void OnEvent(SDL_Event* Event);	 // Capture SDL Events
	
	bool Init();		// Initialize the SDL game/app
	void Loop();		// Logic loop
	void Render();		// Render loop (draw)
	void Cleanup();		// Free up resources

public:
	int Execute(int argc, char* argv[]);

public:
	SDL_Renderer* GetRenderer();

public:
	static App* GetInstance();
	static int GetWindowWidth();
	static int GetWindowHeight();
};

#endif

