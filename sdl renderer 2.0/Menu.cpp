#include "Menu.h"

Menu::Menu()
{
	atMenu = 1;
	f = new Font();
	f->Initialize();
	f->LoadFiles("oneway.ttf", 144);
	f->SetColor(255, 255, 255);
	menuBackground = new Texture("menu720.bmp");
	pauseBackground = new Texture("menu720paused.bmp");
	titleX = 350;
	titleY = 100;
	displayed = false;
	render = true;
}

Menu::Menu(int x, int y)
{
	atMenu = 1;
	f = new Font();
	f->Initialize();
	f->LoadFiles("oneway.ttf", 144);
	f->SetColor(255, 255, 255);
	menuBackground = new Texture("menu720.bmp");
	pauseBackground = new Texture("menu720paused.bmp");
	titleX = int(x * TITLE_X_RATIO);
	titleY = int(y * TITLE_Y_RATIO);
	atMenu = true;
	atPause = false;
	pauseInit = false;
	displayed = false;
}

void Menu::Update(SDL_Surface* screen)
{
	if(render)
	{
		atMenu = true;
		atPause = false;
		menuBackground->Draw(screen, 0, 0);
		f->SetDisplayMessage("Purgatory", TTF_STYLE_NORMAL);
		f->Update(titleX, titleY, screen);
	}
}

void Menu::UpdatePause(SDL_Surface* screen)
{
	if(render)
	{
		atPause = true;
		atMenu = false;
		if(!pauseInit)
		{
			pauseBackground->Draw(screen, 0, 0);
			f->SetDisplayMessage("Purgatory");
			f->Update(titleX, titleY, screen);
			pauseInit = true;
		}
	}
}

void Menu::Shutdown()
{
	atMenu = false;
	atPause = false;
	f->Shutdown();
	f = NULL;
	pauseBackground->Shutdown();
	pauseBackground = NULL;
	menuBackground->Shutdown();
	menuBackground = NULL;
}

bool Menu::AtMenu()
{
	return atMenu;
}

void Menu::ToggleRender()
{
	if(render)
	{
		render = false;
		return;
	}
	else
	{
		render = true;
		return;
	}
}

bool Menu::AtPause()
{
	return atPause;
}

void Menu::TogglePause()
{
	if(atPause)
		atPause = false;
	else
		atPause = true;
}