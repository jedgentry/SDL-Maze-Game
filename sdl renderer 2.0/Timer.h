#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"

class Timer
{
public:
	//Default constructor.
	Timer();
	//Start - Starts the timer.
	void Start();
	//Stop - Stops the timer.
	void Stop();
	//Pause - Pauses the timer.
	void Pause();
	//Unpause - Unpauses the timer.
	void Unpause();
	//GetTicks - returns the number of milliseconds that have passed since the start.
	//@return int - number of milliseconds that have passed.
	int GetTicks();
	//IsStarted - tells if timer has started.
	//@return bool - true if started.
	bool IsStarted();
	//IsPaused - tells if the timer is paused.
	//@return bool - true if paused.
	bool IsPaused();
	//Restart - restarts the timer.
	void Restart();

private:
	//Value of ms since start.
	int startTicks;
	//Value of ms since pause.
	int pausedTicks;
	//amount of times ticks broke the int limit.
	int maxTicks;
	//amount of time ticks broke the int limit.
	int minTicks;
	//is it paused?
	bool paused;
	//Has it started?
	bool started;
};

#endif