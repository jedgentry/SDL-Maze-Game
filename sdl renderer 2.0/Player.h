#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "Texture.h"
#include "Generate.h"
#include <cmath>
#include <time.h>

const int PLAYER_MOVEMENT_SPEED = 1; //In number of blocks.
const int MOVEMENT_INTERVAL = 2;//In 15ms // was 10
const int KICKDOWNS = 3; 

class Player
{
public:
	//default constructor.
	Player();
	//Overloaded constructor.
	//@param int - x value to init player.
	//@param int - y value to init player.
	//@param int - radius of player object.
	//@param int - width of screen.
	//@param int - height of screen.
	Player(int x, int y, int r, int screenWidth, int screenHeight);
	//GetPlayerX - returns the player's X.
	//@return int - value of player's x.
	int GetPlayerX();
	void breakDownWall(int x, int y, Generate* maze);
	//GetPlayerY - returns the player's Y.
	//@return int - value of player's Y.
	int GetPlayerY();
	//SetPlayerX - Sets the player's X value.
	//@param int - x value to set.
	void SetPlayerX(int x);
	//SetPlayerY - Sets the player's Y value.
	//@param int - y value to set.
	void SetPlayerY(int y);
	//GetPlayerXVel - returns the player's xVel.
	//@return int - value of player's x velocity.
	int GetPlayerXVel();
	//GetPlayerYVel - returns the player's y velocity.
	//@return int - value of player's Y velocity.
	int GetPlayerYVel();
	//Update - updates the player object in game loop.
	//@param SDL_Event - Event for the player class to handle.
	//@param SDL_Surface - screen to render the player to.
	void Update(SDL_Event* Event, SDL_Surface* screen, Generate* maze); //Normally takes the block vector
	//Render - renders the player object.
	void Render();
	//Shuts down the player's object.
	void Shutdown();
	void ResetKickdown();
	int GetKickdown() {return kickdown;};
	void StopMovement() {canMove = false;};
	void StartMovement() {canMove = true;};
public:
		//Steps taken, used to calculate score.
	int steps;
private:
	//X location of player.
	int x;
	//Y location of player.
	int y;
	//Radius of player object.
	int r;
	//xVelocity of player.
	int xVel;
	//yVelocity of player.
	int yVel;
	//Render X
	int renderX;
	//Render Y
	int renderY;
	//previous x location of player.
	int prevX;
	//previous y location of player.
	int prevY;
	//Width of the screen.
	int screenWidth;
	//Height of the screen.
	int screenHeight;
	//canmove.
	bool canMove;
	//Pointer to the players texture in memory.
	Texture* playerTexture;
	//Player's timer class to regulate movement.
	int movement;
	//Walls to kick down.
	int kickdown;

private:
	//Distance - Calculates distance between the player and a object.
	//@param int - X2 - location of object to compare.
	//@param int - y location of object to compare.
	//@return double - returns the distance.
	double Distance(int x2, int y2);
	//OnKeyDown - calculates player based on keydown.
	//@param SDLKey sym - key value.
	//@param SDLMod mod - modification on key.
	//@param Uint16 - unicode value of key.
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode, Generate* maze, SDL_Surface* screen);
	//OnKeyUp - calculates player based on keyup
	//@param SDLKey sym - key value.
	//@param SDLMod mod - modification on key.
	//@param Uint16 - unicode value of key.
	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
	//CheckCollision - checks if movement is valid.
	//@return bool - true if valid movement.
};

#endif