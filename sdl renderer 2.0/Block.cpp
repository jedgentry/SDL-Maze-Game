#include "Block.h"

Block::Block()
{
}

Block::Block(SDL_Surface* blockScreen)
{
	this->blockScreen = blockScreen;
	end = false;
	visited = true;
	inRange = true;
	topWall = true;
	leftWall = true;
	rightWall = true;
	bottomWall = true;
	blockRect = new SDL_Rect();
	blockRect->x = 0;
	blockRect->y = 0;
	blockRect->h = BOX_PIXELS;
	blockRect->w = BOX_PIXELS;
	blackBox = new Texture("blackBox.bmp");
	whiteBox = new Texture("whiteBox.bmp");
}
Block::Block(int x, int y, bool topWall, bool leftWall, bool rightWall, bool bottomWall, SDL_Surface* blockScreen)
{
	this->blockScreen = blockScreen;
	blockRect = new SDL_Rect();
	blockRect->x = x;
	blockRect->y = y;
	blockRect->h = BOX_PIXELS;
	blockRect->w = BOX_PIXELS;
	this->topWall = topWall;
	this->leftWall = leftWall;
	this->rightWall = rightWall;
	this->bottomWall = bottomWall;
	end = false;
	blackBox = new Texture("blackBox.bmp");
	whiteBox = new Texture("whiteBox.bmp");
}
Block::Block(int x, int y, bool topWall, bool leftWall, bool rightWall, bool bottomWall, bool end, SDL_Surface* blockScreen)
{
	this->blockScreen = blockScreen;
	blockRect = new SDL_Rect();
	blockRect->x = x;
	blockRect->y = y;
	blockRect->h = BOX_PIXELS;
	blockRect->w = BOX_PIXELS;
	this->topWall = topWall;
	this->leftWall = leftWall;
	this->rightWall = rightWall;
	this->bottomWall = bottomWall;
	this->end = end;
	blackBox = new Texture("blackBox.bmp");
	whiteBox = new Texture("whiteBox.bmp");
}

//Performance sucker, O(n^2)
void Block::DrawBlock()
{
	for(int r = 0; r < BLOCK_SIDE; r++)
	{
		for(int c = 0; c < BLOCK_SIDE; c++)
		{
			if(topWall && r == 0)
			{
				blackBox->Draw(blockScreen, blockRect->x + (r * BOX_PIXELS), blockRect->y + (c * BOX_PIXELS));
			}
			else if(bottomWall && r == BLOCK_SIDE - 1)
			{
				blackBox->Draw(blockScreen, blockRect->x + (r * BOX_PIXELS), blockRect->y + (c * BOX_PIXELS)); 
			}
			else if(leftWall && c == 0)
			{
				blackBox->Draw(blockScreen, blockRect->x + (r * BOX_PIXELS), blockRect->y + (c * BOX_PIXELS)); 
			}
			else if(rightWall && c == BLOCK_SIDE - 1)
			{
				blackBox->Draw(blockScreen, blockRect->x + (r * BOX_PIXELS), blockRect->y + (c * BOX_PIXELS)); 
			}
			else
			{
				whiteBox->Draw(blockScreen, blockRect->x + (r * BOX_PIXELS), blockRect->y + (c * BOX_PIXELS)); 
			}
		}
	}		
}

void Block::Update()
{
	//CHECK VISIBILITY LIMIT
	//if(visiblity limit matched) render;
	DrawBlock();
}

void Block::Shutdown()
{
	//could cause crash
	delete blockRect;
	blackBox->Shutdown();
	whiteBox->Shutdown();
}