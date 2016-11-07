//Hello
#include "Game.h"

using namespace std;

Game::Game(char* directory)
{
	paused = false;
	calculate = false;
	frameRate = NULL;
	timeRunning = NULL;
	menu = NULL;
	startButton = NULL;
	quitButton = NULL;
	menuMusic = NULL;
	particleEngine = NULL;
	player = NULL;
	screen = NULL;
	running = true;
	tutorialDisplayed = false;
	tutorialButton = NULL;
	tutorial = NULL;
	startMaze = false;
	finished = false;
	playerHUD = NULL;
	maze = NULL;
	currentMaze = NULL;
	continueButton = NULL;
	screenRect = new SDL_Rect();
}

bool Game::Initialize()
{

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cerr << "Failed to initialize SDL." << endl;
		return false;
	}
	//This must be called beefore set video mode. 
	//ICON HAS TO BE 24BIT COLOR.
	SDL_Surface* icon = SDL_LoadBMP("purgatoryIcon.bmp");
	if(icon == NULL)
	{
		cerr << "Unable to load icon. Is it 24bit color?" << endl;
	}
	SDL_WM_SetIcon(icon, NULL);
	SetupScreen();
	if((screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
	{
		cerr << "Failed to intialize screen." << endl;
		return false;
	}
	SDL_WM_SetCaption("Purgatory", "Purgatory");
	if(MazeInitialize() == false)
	{
		cerr << "Failed to intialize Maze." << endl;
		return false;
	}
	return true;
}

void Game::Event(SDL_Event* Event)
{
	OnEvent(Event);
}

void Game::Loop(SDL_Event* Event)
{
	if(Event->type == SDL_QUIT)
	{
		Exit();
	}
	if(Event->key.keysym.sym == SDLK_SPACE)
	{
		menu->TogglePause();
	}
	MazeRendering();
}

void Game::Render()
{
	SDL_Flip(screen);
}

void Game::Cleanup()
{
	if(menuMusic)
		menuMusic->Shutdown();
	if(menu)
		menu->Shutdown();
	if(startButton)
		startButton->Shutdown();
	if(quitButton)
		quitButton->Shutdown();
	if(tutorialButton)
		tutorialButton->Shutdown();
	if(maze)
		maze->Shutdown();
	if(player)
		player->Shutdown();
	if(tutorial)
		tutorial->Shutdown();
	if(playerHUD)
		playerHUD->Shutdown();
	if(continueButton)
		continueButton->Shutdown();

	SDL_Quit();
}

int Game::OnExecute()
{
	if(Initialize() == false)
	{
		cerr << "Failed to Initialize on execute." << endl;
		return -1;
	}
	frameRate = new Timer();
	while(running)
	{
		frameRate->Start();
		while(SDL_PollEvent(&Events))
		{
			Event(&Events);
		}
		Loop(&Events);
		Render();
		if(frameRate->GetTicks() < WAIT_TIME)
		{
			SDL_Delay(WAIT_TIME - frameRate->GetTicks());
			frameRate->Restart();
		}
	}
	Cleanup();

	return 0;
}

void Game::Exit()
{
	running = false;
}

void Game::SetupScreen()
{
	// Get Screen Resolution
	//SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN) / 2;
	//SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN) / 2;
	//Overriding till math is fixed.
	SCREEN_WIDTH = 784;
	SCREEN_HEIGHT = 784;
	HDC hdc = GetDC(NULL);
	SCREEN_BPP = GetDeviceCaps(hdc, BITSPIXEL);
	ReleaseDC(NULL, hdc);
	screenRect->x = 0;
	screenRect->y = 0;
	screenRect->w = SCREEN_WIDTH;
	screenRect->h = SCREEN_HEIGHT;
}

void Game::MazeRendering()
{
	if(menu->AtMenu() && startMaze == false)
	{
		menu->Update(screen);
		
		if(startButton->Update(screen, &Events))
		{
			if(currentMaze == NULL)
			{
				currentMaze = maze;
			}
			startMaze = true;
			quitButton->ToggleRender();
			startButton->ToggleRender();
			menu->ToggleRender();
			playerHUD->StartTimer();
			//Set menu->at Menu to false, then begin game logic.
		}
		if(quitButton->Update(screen, &Events))
		{
			OnExit();
		}
		if(tutorialButton->Update(screen, &Events))
		{
			tutorialDisplayed = true;
		}
		if(tutorialDisplayed)
		{
			tutorial->Update(screen, SCREEN_WIDTH, SCREEN_HEIGHT, &Events);
			if(tutorial->IsFinished())
			{
				tutorialDisplayed = false;
			}
		}

	}
	if(menu->AtPause())
	{
		//menu->UpdatePause(screen);
		//return;
	}
	if(startMaze)
	{
		SDL_FillRect(screen, screenRect, 0x000000);
		//If finished.
		if((player->GetPlayerX() == maze->GetEndXArray()) && (player->GetPlayerY() == maze->GetEndYArray()))
		{

			//Fill for score screen.
			SDL_FillRect(screen, screenRect, 0x111111);
			maze->Initialize();
			maze->ResetVisibility();
			particleEngine->SetX(maze->GetEndX());
			particleEngine->SetY(maze->GetEndY());
			player->SetPlayerX(maze->GetStartXArray());
			player->SetPlayerY(maze->GetStartYArray());
			quitButton->ToggleRender();
			playerHUD->ResetHUDTimer();
			playerHUD->CalculateScore(maze);
			playerHUD->AddLevel();
			player->ResetKickdown();
			if(!quitButton->GetRenderState())
			{
				quitButton->ToggleRender();
			}
			if(quitButton->Update(screen, &Events))
			{
				OnExit();
			}
		}
		else
		{
			//Fill background with black.
			maze->Update(screen);
			//Render the blocks here.
			
			playerHUD->Update(screen, player);
			particleEngine->UpdateMazeGoal(screen);
			//Display score screen if finished
			//If they call hit continue();
			//Set new player coords.
			//Change current maze.
			//Move particle, add up score.
			player->Update(&Events, screen, currentMaze);
		}
	}
}

bool Game::MazeInitialize()
{
	maze = new Generate(SCREEN_WIDTH, SCREEN_HEIGHT, directory);
	if(maze == NULL)
	{
		cerr << "Failed to create maze generator." << endl;
		return false;
	}
	maze->Initialize();
	//maze->GenerateMaze();
	final = clock() - init;
	menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT);
	if(menu == NULL)
	{
		cerr << "Failed to create the menu object." << endl;
		return false;
	}
	menuMusic = new Sound();
	if(!menuMusic->Initialize())
	{
		cerr << "Failed to create the music player." << endl;
		return false;
	}
	else
	{
		menuMusic->LoadFile("1986.wav");
		menuMusic->Play();
	}
	startButton = new Button(int(SCREEN_WIDTH * 0.4), int(SCREEN_HEIGHT * 0.40), 240, 120, "startButton.bmp");
	if(startButton == NULL)
	{
		cerr << "Failed to create the start button." << endl;
		return false;
	}
	continueButton = new Button(int(SCREEN_WIDTH * 0.4), int(SCREEN_HEIGHT * 0.40), 240, 120, "continueButton.bmp");
	if(continueButton == NULL)
	{
		cerr << "Failed to create the continue button." << endl;
		return false;
	}
	quitButton = new Button(int(SCREEN_WIDTH * 0.4), int(SCREEN_HEIGHT * 0.60), 240, 120, "quitButton.bmp");
	if(quitButton == NULL)
	{
		cerr << "Failed to create the quit button." << endl;
		return false;
	}
	tutorialButton = new Button(int(SCREEN_WIDTH * 0.4), int(SCREEN_HEIGHT * 0.80), 240, 120, "tutorialButton.bmp");
	if(tutorialButton == NULL)
	{
		cerr << "Failed to create the quit button." << endl;
		return false;
	}
	player = new Player(maze->GetStartX(), maze->GetStartY(), 8, SCREEN_WIDTH, SCREEN_HEIGHT);
	if(player == NULL)
	{
		cerr << "Failed to create a player." << endl;
		return false;
	}
	particleEngine = new ParticleEngine();
	if(!particleEngine->Initialize(maze->GetEndX(), maze->GetEndY()))
	{
		cerr << "Failed to start ParticleEngine." << endl;
		return false;
	}
	tutorial = new Tutorial();
	if(!tutorial->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		cerr << "Failed to create a Tutorial object." << endl;
		return false;
	}
	playerHUD = new HUD();
	if(!playerHUD->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		cerr << "Failed to create a playerHUD object." << endl;
		return false;
	}
	playerHUD->StopTimer();
	
	//if player has finished.
	//Swap maps.

	//while(generator is running)
	//add maps()

	//Call Random Generator here.
	//1. Call Random Generator.
	//2. Build blocks.
	//3. Push Blocks into map.
	//4. ????
	//5. profit
	return true;
}

//FIX SDL Main overriding horseshit
#ifdef main
#undef main
#endif

int main(int argc, char* argv[])
{
	//For Release
	if(!DEBUG)
	{
		//Get rid of console window.
		FreeConsole();
	}
	else
	{
		cout << "|||||||||||||||||||||||||DEBUG CONSOLE ENABLED||||||||||||||||||||||||" << endl;
	}
	Game* maze = new Game(argv[0]);
	return maze->OnExecute();
}

void Game::OnEvent(SDL_Event* Event)
{
    switch(Event->type)
	{
        case SDL_ACTIVEEVENT:
			{
            switch(Event->active.state)
			{
                case SDL_APPACTIVE:    
					{
                    if (Event->active.gain)
					{
						OnRestore();
					}
                    else               
					{
						OnMinimize();
					}
                    break;
                }
            }
           break;
        }
        case SDL_QUIT: 
			{
            OnExit();
            break;
			}
			
        case SDL_VIDEORESIZE: 
			{
            //OnResize(Event->resize.w,Event->resize.h);
            break;
			}
	}
	switch(Event->key.keysym.sym)
	{
	case SDLK_ESCAPE:
		Game::OnExit();
		break;
	}
}
 
void Game::OnMinimize() 
{
    if(SDL_WM_IconifyWindow() == -1)
	{
		cerr << "Unable to minimize window.";
		Game::OnExit();
	}
}
 
void Game::OnRestore() 
{
    
}

void Game::AlternateFullscreen()
{
		if(SDL_SetVideoMode(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SCREEN_BPP, SDL_SWSURFACE |SDL_FULLSCREEN) == NULL)
		{
			cerr << "Unable to go fullscreen." << endl;
			Game::OnExit();
		}
}
 
void Game::OnResize(int w,int h) 
{
	if(SDL_SetVideoMode(w, h, SCREEN_BPP, SDL_SWSURFACE | SDL_DOUBLEBUF) == NULL)
	{
		cerr << "Unable to resize window." << endl;
		Game::OnExit();
	}
}
 
void Game::OnExit() 
{
	running = false;
}