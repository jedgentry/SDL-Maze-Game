#ifndef BLOCK_H
#define BLOCK_H

/**
THIS CLASS NEEDS SERIOUS RESTRUCTORING BASED ON MAZE OUTPUT.
*/

#include "Texture.h"

//Number of pixels per tileBox.
const int BOX_PIXELS = 16;
//Number of tiles that make up a block.
const int TILES_PER_BLOCK = 16;
//Number of pixels in one whole block.
const int BLOCK_SIZE_PIXELS = BOX_PIXELS * TILES_PER_BLOCK;
//Number of pixels on one side of a block.
const int BLOCK_SIDE_PIXELS = BOX_PIXELS * (TILES_PER_BLOCK / 4);
//How many tiles on a block's side.
const int BLOCK_SIDE = 4;

class Block
{
public:
	//Default constructor.
	Block();
	//Constructor that takes a surface to render to.
	//@param SDL_Surface* pointer to the screen in memory.
	Block(SDL_Surface* screen);
	//Constructor that takes the location and boolean values of walls along with where to render.
	Block(int, int, bool, bool, bool, bool, SDL_Surface*);
	Block(int, int, bool, bool, bool, bool, bool, SDL_Surface*);
	void DrawBlock();
	void Update();
	void Shutdown();
	SDL_Rect* blockRect;
private:
	bool topWall;
	bool bottomWall;
	bool leftWall;
	bool rightWall;
	bool visited;
	bool inRange;
	bool render;
	bool end;
	Texture* verticalWall;
	Texture* horizontalWall;
	Texture* whiteBox;
	Texture* blackBox;
	SDL_Surface* blockScreen;
};

#endif