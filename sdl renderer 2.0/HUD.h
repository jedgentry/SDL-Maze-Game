#ifndef HUD_H
#define HUD_H

#include <string>

#include "Timer.h"
#include "Font.h"
#include "Generate.h"
#include "Player.h"

const double KICKDOWN_X_RATIO = 0.35;
const double KICKDOWN_Y_RATIO = 0.97;
//Where to display level x value according to screen ratio.
const double HUD_LEVEL_X_RATIO = 0.01;
//Where to display level y value according to screen ratio.
const double HUD_LEVEL_Y_RATIO = 0.97;
//Where to display timer X value according to screen ratio.
const double HUD_TIMER_X_RATIO = 0.725;
//Where to display timer Y value according to screen ratio.
const double HUD_TIMER_Y_RATIO = 0.97;
//Where to display score.
const double HUD_SCORE_X_RATIO = 0.4;
//Where to display Y value of score.
const double HUD_SCORE_Y_RATIO = 0.001;
//Size of hud font.
const int HUD_FONT_SIZE = 24;

class HUD
{
public:
	//Default constructor.
	HUD();
	//Initializes the HUD.
	//@param int screenWidth - width of the screen.
	//@param int screenHeight - height of the screen.
	//@return bool - true if successful, false otherwise.
	bool Initialize(int, int);
	//AddLevel - adds a level to the counter.
	void AddLevel();
	//ResetHUDTimer - resets the hud timer.
	void ResetHUDTimer();
	//ResetHUD - Resets the HUD.
	void ResetHUD();
	//Shutdown - shutsdown the hud object.
	void Shutdown();
	//Update - updates the hud object.
	//@param SDL_Surface* - pointer to the screen.
	void Update(SDL_Surface* screen, Player* p);
	//StartTimer - starts the timer.
	void StartTimer();
	//StopTimer - stops the timer.
	void StopTimer();
	//CalculateScore - calculates and sets the score of the player.
	void CalculateScore(Generate* m);
private:
	//Pointer to the huds font.
	Font* hudFont;
	//Pointer to the huds timer.
	Timer* hudTimer;
	//Value representing the width of the screen.
	int screenWidth;
	//Value representing the height of the screen.
	int screenHeight;
	//Value of the level the player is on.
	int level;
	//How many minutes have passed.
	int minutes;
	//How many seconds have passed.
	int seconds;
	//Temporary string for Char* conversion.
	std::string temp;
	//Score of the player
	int score;
private:
	//Calculates the timer's message to display.
	//@return char* - pointer to the message to display
	char* CalculateTimerMessage();
};

#endif