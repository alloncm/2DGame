#include "Timer.h"

Timer::Timer()
{
	last = steady_clock::now();
}

float Timer::Tick()
{
	auto old = last;
	last = steady_clock::now();
	duration<float> time = last-old;
	return time.count();
}
