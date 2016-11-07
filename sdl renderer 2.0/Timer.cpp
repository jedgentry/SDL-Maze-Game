#include "Timer.h"

Timer::Timer()
{
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void Timer::Start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
}

void Timer::Stop()
{
	//Stop the timer
	started = false;
	//Unpause the timer
	paused = false;
}

int Timer::GetTicks()
{
	if(started)
	{
		if(paused)
		{
			return pausedTicks;
		}
		else
		{
			return SDL_GetTicks() - startTicks;
		}
	}
	return 0;
}

void Timer::Unpause()
{
	if(paused)
	{
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		//Reset
		pausedTicks = 0;
	}
}

void Timer::Restart()
{
	started = true;
	paused = false;
	pausedTicks = 0;
	startTicks = 0;
}

bool Timer::IsStarted()
{
	return started;
}

bool Timer::IsPaused()
{
	return paused;
}