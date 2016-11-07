#ifndef MAZETEXTURE_H
#define MAZETEXTURE_H

#include "Texture.h"

class MazeTexture : public Texture
{
public:
	MazeTexture(char* filename, int x, int y);
	void Render(SDL_Surface* screen);
	void Shutdown();
	int x;
	int y;
private:
	Texture* t;
};

#endif