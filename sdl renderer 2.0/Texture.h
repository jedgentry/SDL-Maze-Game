#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <cmath>

class Texture
{
public:
	//Default constructor.
	Texture();
	//Overloaded constructor with the file to load
	//@param char* - file to load.
	Texture(char*);
	//Load - Loads the file into memory.
	//@param char* - file to load.
	//@return bool - true if load was successful.
	bool Load(char* file);
	//Draw - draws the object on screen.
	//@param SDL_Surface* - screen to draw on.
	//@param int - x value to draw.
	//@param int - y valeu to draw.
	//@return bool - true if successful.
	bool Draw(SDL_Surface* screen, int x, int y);
	//DrawKey - draws the texture with color keying.
	//@param SDL_Surface* - screen to draw on.
	//@param int - x location to draw.
	//@param int - y location to draw.
	//@param int - red value to key.
	//@param int - green value to key.
	//@param int - blue value to key.
	//@return bool - true if successful.
	bool DrawKey(SDL_Surface* screen, int x, int y, int r, int g, int b);
	//SwapTexture - swaps the texture.
	//@param char* - filename to load in.
	//@return bool - true if successful.
	bool SwapTexture(char* filename); 
	//GetPrevX - returns previous x value.
	//@return int - value of previous X where the texture was rendered.
	int GetPrevX();
	//GetPrevY - returns the previous y value.
	//@return int - value of the previous Y where the texture was rendered.
	int GetPrevY();
	//Shutdown - Shutsdown the texture.
	void Shutdown();
		//Used for debugging.
	char* debugFilename;
private:
	//Pointer to the texture in memory.
	SDL_Surface* texture;
	//previous X.
	int prevX;
	//Previous Y.
	int prevY;
};

#endif