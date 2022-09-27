#pragma once
#include <chrono>
struct Timer
{
public:
	Timer();
	void start(int inTime);
	void stop();
	bool timeIsUp() const;
	std::chrono::seconds difference() const;
	float complite() const;
private:
	bool running;
	std::chrono::time_point<std::chrono::system_clock> startTime;
	std::chrono::seconds time;
};