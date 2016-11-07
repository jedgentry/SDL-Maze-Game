#ifndef GAME_H
#define GAME_H

#include "SDL_main.h"

#include "Timer.h"
#include "Menu.h"
#include "Button.h"
#include "Sound.h"
#include "ParticleEngine.h"
#include "Player.h"
#include "Tutorial.h"
#include "HUD.h"
#include "Generate.h"

#include <sstream>
#include <Windows.h>
#include <time.h>


#define FPS 60;
const bool DEBUG = true;
const Uint32 WAIT_TIME = Uint32(1000.0) / FPS;
const bool FULLSCREEN = false;

clock_t init, final;

class Game
{
public:
	//Initializes the game.
	//@param char* - directory of the game's exe.
	Game(char* directory);
	//Begins the games execution
	//@return int - 0 if successful, false otherwise.
	int OnExecute();
	//Initializes the required game objects.
	//@return bool - true if successful, false otherwise.
	bool Initialize();
	//Event - handles the game events.
	//@param SDL_Event* Event - the event to handle.
	void Event(SDL_Event* Event);
	//Loop - Main game loop.
	//@param SDL_Event* - the event to handle within the loop.
	void Loop(SDL_Event* Event);
	//Render - renders the objects on screen.
	void Render();
	//Cleans up the game class and objects.
	void Cleanup();
	//Exits the window and shutsdown SDL/OpenGL.
	void Exit();
	//MazeInitialize - INitializes the required maze objects.
	//@return bool - true if successful, false otherwise.
	bool MazeInitialize();
	//MazeRendering - Does the rendering for the maze.
	void MazeRendering();
public:
		//Pointer to the screen.
		SDL_Surface* screen;
		//Screens width in pixels
		int SCREEN_WIDTH;
		//Screens height in pixels.
		int SCREEN_HEIGHT;
		//Screens color depth.
		int SCREEN_BPP;

public:
		//OnMinimize - handles the window being minimized.
        virtual void OnMinimize();
		//OnRestore - handles the window being restored.
        virtual void OnRestore();
		//OnResize - handles the window being resized
		//@param int - width of the window.
		//@param int - height of the window.
        virtual void OnResize(int w,int h);
		//OnExit - handles the window on exit.
        virtual void OnExit();
		//OnEvent - handles the windows events and passes them accordingly.
		//@param SDL_Event* - Event to handle.
		virtual void OnEvent(SDL_Event*);
		//AlternateFullscreen - Currently not functional, alternates between fullscreen and windowed.
		virtual void AlternateFullscreen();
private:
	bool paused;
	//If game is running
	bool running;
	//If tutorial is being displayed
	bool tutorialDisplayed;
	//If maze has started.
	bool startMaze;
	//If the maze has been finished, show finish screen.
	bool finished;
	//Calculate the Score.
	bool calculate;
	//Timer handling frame rate
	Timer* frameRate;
	//Timer handling how long its been running.
	Timer* timeRunning;
	//Pointer to menu object.
	Menu* menu;
	//Pointer to start button.
	Button* startButton;
	//Pointer to quit button.
	Button* quitButton;
	//Pointer to tutorial button.
	Button* tutorialButton;
	//Pointer to the continue button.
	Button* continueButton;
	//Pointer to music during menu.
	Sound* menuMusic;
	//Pointer to particleEngine.
	ParticleEngine* particleEngine;
	//Pointer to player object.
	Player* player;
	//Pointer to tutorial object.
	Tutorial* tutorial;
	//Pointer to player HUD.
	HUD* playerHUD;
	//Pointer to the first maze.
	Generate* maze;
	//Pointer to the events recorded in SDL
	SDL_Event Events;
	//Pointer to what maze is on
	Generate* currentMaze;
	//Rectangle representing entire screen.
	SDL_Rect* screenRect;
	//char* to the directory
	string directory;
private:
	//Sets up and detects screen width, height, and color depth
	void SetupScreen();
};

#endif