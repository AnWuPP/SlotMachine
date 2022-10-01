#include "Timer.h"

Timer::Timer() : running(false),
				startTime(std::chrono::seconds(0)),
				time(std::chrono::seconds(0))
{ }

void Timer::start(int inTime)
{
	if (running)
		return;
	time = std::chrono::seconds(inTime);
	startTime = std::chrono::system_clock::now();
	running = true;
}

bool Timer::isRunning() const {
	return running;
}

void Timer::stop()
{
	if (!running)
		return;
	running = false;
}

bool Timer::timeIsUp() const
{
	if (!running)
		return false;
	auto diff = difference();
	return diff.count() >= time.count();
}

float Timer::complite() const
{
	if (!running)
		return 0.f;
	auto rr = difference();
	auto res = static_cast<float>(rr.count()) / static_cast<float>(time.count());
	return res;
}

std::chrono::seconds Timer::difference() const
{
	if (!running)
		return std::chrono::seconds(0);
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - startTime);
}