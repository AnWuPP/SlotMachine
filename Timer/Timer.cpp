#include "Timer.h"

Timer::Timer() : running(false),
				startTime(std::chrono::seconds(0)),
				time(std::chrono::seconds(0))
{ }

void Timer::start(int inTime)
{
	if (running || inTime < 1)
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
	return diff >= static_cast<float>(time.count());
}

float Timer::complite() const
{
	if (!running)
		return 0.f;
	auto rr = difference();
	auto res = rr / static_cast<float>(time.count());
	return res;
}

float Timer::difference() const
{
	if (!running)
		return 0.f;
	return static_cast<float>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - startTime).count());
}