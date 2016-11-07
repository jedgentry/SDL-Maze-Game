#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"
#include "Timer.h"


class Button
{
public:
	//Default constructor.
	Button();
	//Overloaded constructor.
	//@param int - x location on screen.
	//@param int - y location on screen.
	//@param int - w width of button.
	//@param int - h height of button.
	//@param char* - name of the file to load in.
	Button(int x, int y, int w, int h, char* filename);
	//Update - updates the button in the game loop.
	//@param SDL_Surface* screen - pointer to the screen.
	//@param SDL_Event* event - pointer to the event for the button to respond to.
	//@return bool - true if clicked.
	bool Update(SDL_Surface* screen, SDL_Event* Event);
	//UpdateWithKey - Updates and color keys.
	//@param SDL_Surface* screen - pointer to the screen.
	//@param SDL_Event* event - pointer to the Event.
	//@param Uint8 - Red value to key.
	//@param Uint8 - Green value to key.
	//@param Uint8 - Blue value to key.
	//@return - true if clicked, false otherwise.
	bool UpdateWithKey(SDL_Surface* screen, SDL_Event* Event, Uint8 r, Uint8 g, Uint8 b);
	//HandleEvents - Manage's the buttons Event.
	//@param SDL_Event* - Pointer to the event to manage.
	//@return bool - true if clicked, false otherwise.
	bool HandleEvents(SDL_Event* Event);
	//SwapTexture - Swaps the texture of the button (ie checkbox)
	//@param char* - filename to load in.
	//@return bool - true if successful in loading, false otherwise.
	bool SwapTexture(char* filename);
	//GetRenderState - returns if item is rendering.
	//@return bool - true if object is rendering.
	bool GetRenderState() {return display;};
	//ToggleRender - enables or disables rendering of the button.
	void ToggleRender();
	//Shutdown - Shutsdown the button object.
	void Shutdown();
private:
	//Pointer to the button
	Texture* buttonTexture;
	//SDL_Rect rectangle struct of the buttons dimensions and location.
	SDL_Rect box;
	//Position of the X value of the mouse.
	int mouseX;
	//Position of the Y value of the mouse.
	int mouseY;
	//Display - whether or not to display the button.
	bool display;
};

#endif