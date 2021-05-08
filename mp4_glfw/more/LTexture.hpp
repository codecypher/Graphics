/*
 * LTexture.hpp
 * Texture wrapper class
 * 
 * We wrap the SDL_Texture in a class to make some things easier.
 * If we want to get certain information about the texture such as its width or height 
 * we would have to use some SDL functions to query the information for the texture.
 * So we use a class to wrap and store the information about the texture.
 */
#pragma once

#ifndef __LTEXTURE_H__
#define __LTEXTURE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

 // C++ header files
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


// C header files
#include <stdio.h>


class AppSDL;  // forward declaration (circular dependency)


class LTexture {
public:
	LTexture();			// Initialize variables
	~LTexture();		// Deallocate memory

	LTexture(AppSDL*ptr);	// Initialize variables

	virtual void free();																// Deallocate texture
	virtual bool loadFromFile(std::string path);										// Load image from specified path			
	//virtual bool loadFromRenderedText(std::string textureText, SDL_Color textColor);	// Create image from font string
	virtual void setColor(Uint8 red, Uint8 green, Uint8 blue);							// Set color modulation
	virtual void setBlendMode(SDL_BlendMode blending);									// Set blending
	virtual void setAlpha(Uint8 alpha);													// Set alpha modulation

	// Render texture at given point
	virtual void render(
		int x, 
		int y, 
		SDL_Rect* clip = NULL, 
		double angle = 0.0,
		SDL_Point* center = NULL, 
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();
	int getHeight();

private:
	AppSDL* root = NULL;
	SDL_Texture* mTexture = NULL;	// pointer to the actual hardware texture

	// Image dimensions
	int mWidth;
	int mHeight;
};

#endif
