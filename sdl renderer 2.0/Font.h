#ifndef FONT_H
#define FONT_H

#include "SDL.h"
#include "SDL_main.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include <iostream>

class Font
{
public:
	//Default constructor.
	Font();
	//Initializes the font class and required SDL objects.
	//@return bool - true if successful, false otherwise.
	bool Initialize();
	//Loads the files into memory.
	//@param const char* - the name of the font to load.
	//@param const int size - the size that the font will be.
	//@return bool - true if successful, false otherwise.
	bool LoadFiles(const char* name, const int size);
	//SetDisplayMessage - sets the message to display on the screen.
	//@param char* - the message to display.
	void SetDisplayMessage(char* message);
	//SetDisplayMessage - sets the message to display on the screen with the selected font style.
	//@param char* - the message to display.
	void SetDisplayMessage(char* message, int style);
	//Update - Updates the font on screen.
	//@param int x - x location on screen.
	//@param int y - y location on screen.
	//@param SDL_Surface* screen - pointer to the screen.
	void Update(int x, int y, SDL_Surface* screen);
	//Shutdown - shutsdown the font class.
	void Shutdown();
	//SetColor - sets the color of the font.
	//@param int r - red value to set.
	//@param int g - green value to set.
	//@param int b - blue value to set.
	void SetColor(int r, int g, int b);
private:
	//Pointer to the font in memory.
	TTF_Font *font;
	//Pointer to the color struct in memory.
	SDL_Color textColor;
	//Pointer to the message in memory.
	SDL_Surface* displayMessage;
};

#endif