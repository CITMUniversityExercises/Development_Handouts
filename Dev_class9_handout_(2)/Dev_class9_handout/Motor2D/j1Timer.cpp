// ----------------------------------------------------
// j1Timer.cpp
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "j1Timer.h"
#include "SDL\include\SDL_timer.h"
#include "p2Log.h"

// ---------------------------------------------
j1Timer::j1Timer()
{
	Start();
}

// ---------------------------------------------
void j1Timer::Start()
{
	// TODO 1: Fill Start(), Read(), ReadSec() methods
	// they are simple, one line each!

	started_at = SDL_GetTicks();
}

// ---------------------------------------------
uint32 j1Timer::Read() const
{
	current_time = SDL_GetTicks();

	return 0;
}

// ---------------------------------------------
float j1Timer::ReadSec() const
{

	LOG("time is: ", current_time-started_at);

	return current_time - started_at;
}