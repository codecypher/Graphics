#include "LWindow.h"

#include <sstream>

LWindow::LWindow(Lesson *ptr) {
	// Initialize non-existant window
	mWindow = NULL;
	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mMinimized = false;
	mWidth = 0;
	mHeight = 0;
	root = ptr;
}

bool LWindow::init() {
	// Create the window with the SDL_WINDOW_RESIZABLE flag which allows for our window to be resizable. 
	// If the function succeeds we set the corresponding flags and dimensions. 
	// Then we return whether the window is null
	mWindow = SDL_CreateWindow("SDL Tutorial", 
							   SDL_WINDOWPOS_UNDEFINED, 
							   SDL_WINDOWPOS_UNDEFINED, 
							   SCREEN_WIDTH, 
							   SCREEN_HEIGHT, 
							   SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (mWindow != NULL) {
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;
	}

	return mWindow != NULL;
}

// Handle the creation of a renderer from the member window. 
// We are returning the created renderer because rendering will be handled outside of the class.
SDL_Renderer* LWindow::createRenderer() {
	return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void LWindow::handleEvent(SDL_Event& e) {
	// Window event occured
	if (e.type == SDL_WINDOWEVENT) {
		// Caption update flag
		// Depending on the event we may have to update the caption of the window
		bool updateCaption = false;

		// When we have a window event we then want to check 
		// the SDL_WindowEventID to find the type of event
		switch (e.window.event) {
			// Get new dimensions and repaint on window size change
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				mWidth = e.window.data1;
				mHeight = e.window.data2;
				SDL_RenderPresent(gRenderer);
				break;

			// Repaint on exposure
			// The window was obscured in some way and now is not obscured 
			// so we want to repaint the window.
			case SDL_WINDOWEVENT_EXPOSED:
				SDL_RenderPresent(gRenderer);
				break;

			// Mouse entered window
			case SDL_WINDOWEVENT_ENTER:
				mMouseFocus = true;
				updateCaption = true;
				break;

			// Mouse left window
			case SDL_WINDOWEVENT_LEAVE:
				mMouseFocus = false;
				updateCaption = true;
				break;

			// Window has keyboard focus
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				mKeyboardFocus = true;
				updateCaption = true;
				break;

			// Window lost keyboard focus
			case SDL_WINDOWEVENT_FOCUS_LOST:
				mKeyboardFocus = false;
				updateCaption = true;
				break;

			// Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
				mMinimized = true;
				break;

			// Window maxized
			case SDL_WINDOWEVENT_MAXIMIZED:
				mMinimized = false;
				break;

			// Window restored
			case SDL_WINDOWEVENT_RESTORED:
				mMinimized = false;
				break;
		}

		// Update window caption with new data
		if (updateCaption) {
			// Load a string stream with the updated data and update the caption
			std::stringstream caption;
			caption << "SDL Tutorial - MouseFocus:" << ((mMouseFocus) ? "On" : "Off") << " KeyboardFocus:" << ((mKeyboardFocus) ? "On" : "Off");
			SDL_SetWindowTitle(mWindow, caption.str().c_str());
		}
	}
	// Enter exit full screen on return key
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
		if (mFullScreen) {
			SDL_SetWindowFullscreen(mWindow, SDL_FALSE);
			mFullScreen = false;
		}
		else {
			SDL_SetWindowFullscreen(mWindow, SDL_TRUE);
			mFullScreen = true;
			mMinimized = false;
		}
	}
}

void LWindow::free() {
	if (mWindow != NULL) {
		SDL_DestroyWindow(mWindow);
	}

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}

int LWindow::getWidth() {
	return mWidth;
}

int LWindow::getHeight() {
	return mHeight;
}

bool LWindow::hasMouseFocus() {
	return mMouseFocus;
}

bool LWindow::hasKeyboardFocus() {
	return mKeyboardFocus;
}

bool LWindow::isMinimized() {
	return mMinimized;
}
