/*
	Texture class for wrapping SDL Textures
	
	Wraps SDL Textures into a more streamlined Texture class for easy loading and rendering.

	The TextureBank class is used loading multiple textures at once and a FileManager class 
	for reading directories (with iOS support).
*/
#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class Texture {
private:
	std::string Filename;

	int Width = 0;
	int Height = 0;

	SDL_Renderer* Renderer = NULL;
	SDL_Texture* SDLTexture = NULL;
	TTF_Font* gFont = NULL;				// Globally used font

public:
	Texture();
	~Texture();

	bool Load(SDL_Renderer* Renderer, std::string Filename);

	void Render(int X, int Y);
	void Render(int X, int Y, int Width, int Height);
	void Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight);

	int GetWidth();
	int GetHeight();
};

#endif

