#include "MazeTexture.h"

MazeTexture::MazeTexture(char* filename, int x, int y)
{
	t = new Texture(filename);
	this->x = x;
	this->y = y;
}

void MazeTexture::Shutdown()
{
	t->Shutdown();
}

void MazeTexture::Render(SDL_Surface* screen)
{
	t->Draw(screen, x, y);
}