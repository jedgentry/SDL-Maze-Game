#include "HUD.h"

HUD::HUD()
{
	screenWidth = 0;
	screenHeight = 0;
	hudTimer = NULL;
	hudFont = NULL;
	level = 0;
	minutes = 0;
	seconds = 0;
	temp = "";
	score = 0;
}

void HUD::AddLevel()
{
	level += 1;
}

void HUD::CalculateScore(Generate* m)
{
	score += m->GetSteps();
}

void HUD::StopTimer()
{
	hudTimer->Stop();
}

void HUD::StartTimer()
{
	hudTimer->Start();
}

bool HUD::Initialize(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	hudFont = new Font();
	if(!hudFont)
	{
		std::cerr << "Unable to intialize HUD Font." << std::endl;
		return false;
	}
	hudFont->Initialize();
	hudFont->LoadFiles("oneway.ttf", HUD_FONT_SIZE);
	hudFont->SetColor(200, 0, 0);
	hudTimer = new Timer();
	if(!hudTimer)
	{
		std::cerr << "Unable to intialize HUD Timer." << std::endl;
		return false;
	}
	hudTimer->Start();
	return true;
}

void HUD::Update(SDL_Surface* screen, Player* p)
{
	temp = "Kickdowns: " + std::to_string(long double(p->GetKickdown()));
	hudFont->SetDisplayMessage((char*)temp.c_str());
	hudFont->Update(int(screenWidth * KICKDOWN_X_RATIO), int(screenHeight * KICKDOWN_Y_RATIO), screen);
	temp = "Level: " + std::to_string(long double (level));
	hudFont->SetDisplayMessage((char*)temp.c_str());
	hudFont->Update(int(screenWidth * HUD_LEVEL_X_RATIO), int(screenHeight * HUD_LEVEL_Y_RATIO), screen);
	hudFont->SetDisplayMessage(CalculateTimerMessage());
	hudFont->Update(int(screenWidth * HUD_TIMER_X_RATIO), int(screenHeight * HUD_TIMER_Y_RATIO), screen);
}


char* HUD::CalculateTimerMessage()
{
	minutes = (hudTimer->GetTicks() / 1000) / 60;
	seconds = (hudTimer->GetTicks() / 1000) - (minutes * 60); 
	if(seconds < 10)
	{
		temp = "Time Played: " + std::to_string(long double(minutes)) + ":0" + std::to_string(long double(seconds));
	}
	else
	{
		temp = "Time Played: " + std::to_string(long double(minutes)) + ':' + std::to_string(long double(seconds));
	}
	return (char*)temp.c_str();
}

void HUD::ResetHUD()
{
	ResetHUDTimer();
	level = 0;
}

void HUD::ResetHUDTimer()
{	seconds = 0;
	minutes = 0;

}

void HUD::Shutdown()
{
	hudTimer->Stop();
	hudFont->Shutdown();
	hudTimer = NULL;
	hudFont = NULL;
}