#ifndef MENU_H
#define MENU_H

#include "Font.h"
#include "Texture.h"

//Ratio to display the title.
const double TITLE_X_RATIO = 0.17;
const double TITLE_Y_RATIO = 0.14;

class Menu
{
public:
	//Default constructor.
	Menu();
	//Default Constructor
	//@param int x - x value of menu.
	//@param int y - y value of menu.
	Menu(int x, int y);
	//Update - updates the menu.
	//@param SDL_Surface* - screen to render.
	void Update(SDL_Surface* screen);
	//Shutdown - shutsdown the menu.
	void Shutdown();
	//GetStatus - gets the status of the menu.
	bool GetStatus();
	//UpdatePause - updates the Pause menu when paused.
	//@param SDL_Surface* - pointer to the screen.
	void UpdatePause(SDL_Surface* screen);
	//AtMenu - returns true if at menu.
	//@return bool - true if at menu.
	bool AtMenu();
	//AtPause - returns true if paused.
	//@return bool - true if paused.
	bool AtPause();
	//ToggleRender - toggles the menus rendering.
	void ToggleRender();
	//TogglePause - toggles the pause menu.
	void TogglePause();
private:
	//Font of the menu.
	Font* f;
	//Background image of the menu.
	Texture* menuBackground;
	//Background image of the pause menu.
	Texture* pauseBackground;
	//X value of the titles location.
	int titleX;
	//Y value of the titles location.
	int titleY;
	//If menu is being displayed.
	bool displayed;
	//If player is paused.
	bool atPause;
	//If player is at the menu.
	bool atMenu;
	//If the pause was initialized successfully.
	bool pauseInit;
	//If menu is to be rendered.
	bool render;
};

#endif