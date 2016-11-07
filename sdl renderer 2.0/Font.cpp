#include "Font.h"

Font::Font()
{
	font = NULL;
	textColor.b = 255;
	textColor.g = 255;
	textColor.r = 255;
	displayMessage = NULL;
}

bool Font::Initialize()
{
	if(TTF_Init() == -1)
	{
		std::cerr << "Failed to intialize TTF_INIT()." << std::endl;
		return false;
	}

	return true;
}

void Font::SetDisplayMessage(char* message)
{
	if(font == NULL)
	{
		std::cerr << "Failed to display message due to NULL font." << std::endl;
		return;
	}
	SDL_FreeSurface(displayMessage);
	displayMessage = TTF_RenderText_Solid(font, message, textColor);
}

void Font::SetDisplayMessage(char* message, int style)
{
	if(font == NULL)
	{
		std::cerr << "Failed to display message due to NULL font." << std::endl;
		return;
	}
	TTF_SetFontStyle(font, style);
	SDL_FreeSurface(displayMessage);
	displayMessage = TTF_RenderText_Solid(font, message, textColor);
}

void Font::Update(int x, int y, SDL_Surface* screen)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(displayMessage, NULL, screen, &offset); 
}

bool Font::LoadFiles(const char* name, const int size)
{
	font = TTF_OpenFont(name, size);
	if(font == NULL)
	{
		std::cerr << "Failed to display message due to NULL font." << std::endl;
		return false;
	}
	//Set font style to bold to help with clarity
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	return true;
}

void Font::SetColor(int red, int green, int blue)
{
	textColor.b = blue;
	textColor.g = green;
	textColor.r = red;
}

void Font::Shutdown()
{
	TTF_Quit();
	font = NULL;
}