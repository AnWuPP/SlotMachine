#include "Interface.h"
Timer::Timer() : running(false),
				_start(std::chrono::seconds(0)),
				_end(std::chrono::seconds(0)),
				_time(std::chrono::seconds(0))
{ }

void Timer::start(int time)
{
	if (running)
		return;
	_time = std::chrono::seconds(time);
	_start = std::chrono::system_clock::now();
	running = true;
}

void Timer::stop()
{
	if (!running)
		return;
	running = false;
}

bool Timer::time_is_up()
{
	if (!running)
		return false;
	auto diff = difference();
	return diff >= _time;
}

std::chrono::seconds Timer::difference()
{
	if (!running)
		return std::chrono::seconds(0);
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _start);
}