#include "Tutorial.h"

Tutorial::Tutorial()
{
	finished = false;
	tutorialPlayer = NULL;
	tutorialParticle = NULL;
	tutorialFont = NULL;
	tutorialButton = NULL;
}

bool Tutorial::Initialize(int screenWidth, int screenHeight)
{
	tutorialPlayer = new Texture("playerTexture.bmp");
	if(tutorialPlayer == NULL)
	{
		cerr << "Unable to load in playerTexture.bmp." << endl;
		return false;
	}
	tutorialParticle = new ParticleEngine();
	if(tutorialParticle == NULL)
	{
		cerr << "Unable to create particle engine." << endl;
		return false;
	}
	tutorialParticle->Initialize(int(screenWidth * 0.65), int(screenHeight * 0.15));
	tutorialFont = new Font();
	if(tutorialFont == NULL)
	{
		cerr << "Unable to create tutorial font. " << endl;
		return false;
	}
	tutorialFont->Initialize();
	tutorialFont->LoadFiles("oneway.ttf", 18);
	tutorialButton = new Button(int(screenWidth * 0.85) - 16, int(screenHeight * 0.1), 16, 16, "redX.bmp");
	if(tutorialButton == NULL)
	{
		cerr << "Unable to create tutorialButton." << endl;
		return false;
	}
	tutorialFont->SetColor(255, 255, 255);

	screenRect.x = int(screenWidth * 0.10);
	screenRect.y = int(screenHeight * 0.10);
	screenRect.w = int(screenWidth * 0.75);
	screenRect.h = int(screenHeight * 0.75);

	return true;
}

void Tutorial::Update(SDL_Surface* screen, int screenWidth, int screenHeight, SDL_Event* Event)
{
	//Black out the screen behind everything.
	SDL_FillRect(screen, &screenRect, 0x111111);
	//Display player tutorial information.
	tutorialFont->SetDisplayMessage("This is you ");
	tutorialFont->Update(int(screenWidth * 0.15), int(screenHeight * 0.15), screen);
	tutorialPlayer->Draw(screen, int(screenWidth * 0.2), int(screenHeight * 0.2));
	//Display goal information.
	tutorialFont->SetDisplayMessage("Your goal is to touch this object to go to the next level:");
	tutorialFont->Update(int(screenWidth * 0.25), int(screenHeight * 0.1), screen);
	//Display particle engine here.
	tutorialParticle->Update(screen, int(screenWidth * 0.65), int(screenHeight * 0.15), 3, 3);
	//Final goal info
	tutorialFont->SetDisplayMessage("Simple? Heh. Try escaping.");
	tutorialFont->Update(int(screenWidth * 0.4), int(screenHeight * 0.5), screen);
	tutorialFont->SetDisplayMessage("Press IJKL to kick down a wall in that respective direction.");
	tutorialFont->Update(int(screenWidth * 0.125), int(screenHeight * 0.6), screen);
	tutorialFont->SetDisplayMessage("Remember you only have three!");
	tutorialFont->Update(int(screenWidth * 0.125), int(screenHeight * 0.7), screen);
	tutorialFont->SetDisplayMessage("Use WASD or the arrow keys to move in their respective directions.");
	tutorialFont->Update(int(screenWidth * 0.125), int(screenHeight * 0.8), screen);
	if(tutorialButton->Update(screen, Event))
	{
		finished = true;
	}
}

bool Tutorial::IsFinished()
{
	if(finished)
	{
		finished = false;
		return true;
	}
	else
	{
		return false;
	}
}

void Tutorial::Shutdown()
{
	tutorialFont->Shutdown();
	tutorialPlayer->Shutdown();
	tutorialButton->Shutdown();
	tutorialParticle->Shutdown();
}