#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Texture.h"
#include "ParticleEngine.h"
#include "Font.h"
#include "Button.h"


class Tutorial
{
public:
	//Default constructor.
	Tutorial();
	//Initialize - Initializes the button object.
	//@param int - screenWidth.
	//@param int - screenHeight.
	//@return bool - true if successful.
	bool Initialize(int screenWidth, int screenHeight);
	//Update - updates the screen object.
	//@param SDL_Surface* - screen to render to.
	//@param int - screenWidth.
	//@param int - screenHeight.
	//@param SDL_Event* - event to handle.
	void Update(SDL_Surface* screen, int screenWidth, int screenHeight, SDL_Event* Event);
	//IsFinished - if the player has tutorial closed.
	//@return bool - returns true if paused.
	bool IsFinished();
	//Shutdown - Shutsdown the button object.
	void Shutdown();
private:
	//True if finished with tutorial
	bool finished;
	//Texture of the player to display.
	Texture* tutorialPlayer;
	//Texture of the particleEngine to display.
	ParticleEngine* tutorialParticle;
	//Font to use in tutorial.
	Font* tutorialFont;
	//Button to use in tutorial.
	Button* tutorialButton;
	//Rectangle represeting the tutorial overlay.
	SDL_Rect screenRect;
};

#endif