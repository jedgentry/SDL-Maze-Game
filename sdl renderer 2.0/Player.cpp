#include "Player.h"

Player::Player()
{
	x = 0;
	y = 0;
	xVel = 0;
	yVel = 0;
	playerTexture = new Texture("playerTexture.bmp");
	steps = 0;
	kickdown = KICKDOWNS;
}

Player::Player(int x, int y, int r, int screenWidth, int screenHeight)
{
	kickdown = KICKDOWNS;
	movement = 0;
	canMove = true;
	playerTexture = NULL;
	renderX = x;
	renderY = y;
	this->x = x / BLOCK_SIZE;
	this->y = y / BLOCK_SIZE;
	this->r = r;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	prevX = 0;
	prevY = 0;
	playerTexture = new Texture("playerTexture.bmp");
	if(playerTexture == NULL)
	{
		std::cerr << "Unable to load playerTexture.bmp" << std::endl;
	}
}

void Player::ResetKickdown()
{
	kickdown = KICKDOWNS;
}

int Player::GetPlayerXVel()
{
	return prevX;
}

void Player::SetPlayerX(int x)
{
	this->x = x;
}

void Player::SetPlayerY(int y)
{
	this->y = y;
}

int Player::GetPlayerYVel()
{
	return prevY;
}

void Player::Shutdown()
{
	playerTexture->Shutdown();
}

void Player::Update(SDL_Event* Event, SDL_Surface* screen, Generate* maze)
{
	for(int visibleX = x - 1; visibleX <= x + 1; visibleX++)
	{
		if(visibleX > MAZE_SIZE || visibleX < 0)
			break;
		for(int visibleY = y - 1; visibleY <= y + 1; visibleY++)
		{
			if(visibleY > MAZE_SIZE || visibleY < 0)
				break;
			maze->mazeBlocks[visibleX][visibleY]->rendered = true;
		}
	}
	if(Event->type == SDL_KEYDOWN)
	{
		OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode, maze, screen);
	}
	if(Event->type == SDL_KEYUP)
	{
		OnKeyUp(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
	}
	renderX = x * BLOCK_SIZE;
	renderY = y * BLOCK_SIZE;
	if(movement > MOVEMENT_INTERVAL && !canMove)
	{
		canMove = true;
		movement = 0;
	}

	playerTexture->DrawKey(screen, renderX, renderY, 255, 255, 255);

	if(!canMove)
	{
		movement++;
	}
}

double Player::Distance(int x2, int y2)
{
	//Return distance between points
	return sqrt(pow(double(x2 - x), 2) + pow(double(y2 - y), 2));
}

int Player::GetPlayerX()
{
	return x;
}

int Player::GetPlayerY()
{
	return y;
}

void Player::breakDownWall(int x, int y, Generate* maze)
{
	if(x < 1 || y < 1 || x > (MAZE_SIZE - 2) || y > (MAZE_SIZE - 2))
		return;
	else
	{
		if(maze->mazeBlocks[x][y]->moveable)
			return;
		else if(kickdown > 0)
		{
			maze->mazeBlocks[x][y]->blockTexture->SwapTexture("whiteSquare.bmp");
			maze->mazeBlocks[x][y]->moveable = true;
			kickdown--;
		}
	}
}

void Player::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode, Generate* maze, SDL_Surface* screen) 
{
    switch(sym)
	{
		case SDLK_UP:
			if(maze->mazeBlocks[x][y - 1]->moveable && canMove)
			{
				prevY = y;
				y -= PLAYER_MOVEMENT_SPEED;
				canMove = false;
			}
			break;
		case SDLK_i:
			breakDownWall(x, y - 1, maze);
			break;
		case SDLK_w:
			if(maze->mazeBlocks[x][y - 1]->moveable && canMove)
			{
				prevY = y;
				y -= PLAYER_MOVEMENT_SPEED;
				canMove = false;
			}
			break;
        case SDLK_DOWN:
			if(maze->mazeBlocks[x][y + 1]->moveable && canMove)
			{
				prevY = y;
				y += PLAYER_MOVEMENT_SPEED;
				canMove = false;
			}
			break;
		case SDLK_s:
			if(maze->mazeBlocks[x][y + 1]->moveable && canMove)
			{
				prevY = y;
				y += PLAYER_MOVEMENT_SPEED;
				canMove = false;
			}
			break;
		case SDLK_k:
			breakDownWall(x, y + 1, maze);
			break;
        case SDLK_LEFT:
			if(maze->mazeBlocks[x - 1][y]->moveable && canMove)
			{
				prevX = x;
				x -= PLAYER_MOVEMENT_SPEED;
				canMove = false;
			}
			break;
		case SDLK_j:
			breakDownWall(x - 1, y, maze);
			break;
		case SDLK_a:
			if(maze->mazeBlocks[x - 1][y]->moveable && canMove)
			{
				prevX = x;
				x -= PLAYER_MOVEMENT_SPEED;
				canMove = false;
			}
			break;
        case SDLK_RIGHT:
			if(maze->mazeBlocks[x + 1][y]->moveable && canMove)
			{
				prevX = x;
				x += PLAYER_MOVEMENT_SPEED;
				canMove = false;
			}
			break;
		case SDLK_d:
			if(maze->mazeBlocks[x + 1][y]->moveable && canMove)
			{
				prevX = x;
				x += PLAYER_MOVEMENT_SPEED;
				canMove = false;
			}
			break;
		case SDLK_l:
			breakDownWall(x + 1, y, maze);
			break;
		case SDLK_f:
			x = maze->GetEndXArray();
			y = maze->GetEndYArray();
		default:
			break;

		if(x < 0)
			x = 0;
		if(y < 0)
			y = 0;
		if(x > MAZE_SIZE)
			x = MAZE_SIZE - 1;
		if(y > MAZE_SIZE)
			y = MAZE_SIZE - 1;
	}
}

//Disposable
void Player::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	switch(sym)
	{
		case SDLK_UP:
			y = y;
			break;
		case SDLK_w:
			y = y;
			break;
		case SDLK_DOWN:
			y = y;
			break;
		case SDLK_s:
			y = y;
			break;
		case SDLK_LEFT:
			x = x;
			break;
		case SDLK_a:
			x = x;
			break;
		case SDLK_RIGHT:
			x = x;
			break;
		case SDLK_d:
			x = x;
			break;
		default:
			x = x;
			y = y;
			break;
	}
}