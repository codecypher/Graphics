#pragma once

#ifndef __LWINDOW_H__
#define __LWINDOW_H__

#include <SDL2/SDL.h>

class Lesson;  // forward declaration (circular dependency)

class LWindow {
private:
	// Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

public:
	// Intialize internals
	//LWindow();
	LWindow(Lesson* ptr);

	// Creates window
	bool init();

	// Creates renderer from internal window
	SDL_Renderer* createRenderer();

	// Handles window events
	void handleEvent(SDL_Event& e);

	// Deallocates internals
	void free();

	// Window dimensions
	int getWidth();
	int getHeight();

	// Window focus handlers
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();

private:
	Lesson* root;

	// The window renderer
	SDL_Renderer* gRenderer = NULL;

	// Window data
	SDL_Window* mWindow;

	// Window dimensions
	int mWidth;
	int mHeight;

	// Window focus
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
};



#endif