#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(char* file)
{
	if(Load(file) == false)
	{
		//Force crash
		std::cerr << "Unable to load " << file << std::endl;
		Shutdown();
	}
}

bool Texture::Load(char* file)
{
	debugFilename = file;

	SDL_Surface* temp = NULL;
	SDL_Surface* result = NULL;

	if((temp = IMG_Load(file)) == NULL)
	{
		std::cerr << "Failed to load texture: " << file << "\n Check your filepath, location, and type." << std::endl;
		return false;
	}

	result = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	texture = result;

	return true;
}

bool Texture::DrawKey(SDL_Surface* screen, int x, int y, int r, int g, int b)
{
	if(screen == NULL || texture == NULL)
	{
		if(screen == NULL)
		{
			std::cerr << "Cannot draw due to screen being NULL'd." << std::endl;
		}
		if(texture == NULL)
		{
			std::cerr << "Cannot draw due to texture being NULL'd." << std::endl;
		}

		return false;
	}

	SDL_Rect destination;

	destination.x = x;
	destination.y = y;

	prevX = x;
	prevY = y;


	SDL_SetColorKey(texture, SDL_SRCCOLORKEY, SDL_MapRGB(texture->format, r, g, b));
	SDL_BlitSurface(texture, NULL, screen, &destination);

	return true;
}

bool Texture::SwapTexture(char* filename)
{
	SDL_FreeSurface(texture);
	if(!Load(filename))
		return false;

	return true;
}

bool Texture::Draw(SDL_Surface* screen, int x, int y)
{
	if(screen == NULL || texture == NULL)
	{
		if(screen == NULL)
		{
			std::cerr << "Cannot draw due to screen being NULL'd." << std::endl;
		}
		if(texture == NULL)
		{
			std::cerr << "Cannot draw due to texture being NULL'd." << std::endl;
		}

		std::cout << "Filename: " << debugFilename << std::endl;

		return false;
	}

	SDL_Rect destination;

	destination.x = x;
	destination.y = y;

	prevX = x;
	prevY = y;
	if(SDL_BlitSurface(texture, NULL, screen, &destination) == -1)
	{
		std::cerr << "FAILED TO BLIT" << debugFilename << std::endl;
		return false;
	}

	return true;
}

int Texture::GetPrevX()
{
	return prevX;
}

int Texture::GetPrevY()
{
	return prevY;
}

void Texture::Shutdown()
{
	if(texture == NULL)
		return;

	SDL_FreeSurface(texture);
	texture = NULL;
}