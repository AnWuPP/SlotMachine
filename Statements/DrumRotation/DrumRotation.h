#pragma once

#include "../Statements.h"
#include "../../Timer/Timer.h"

constexpr int pauseTime = 2;
constexpr int minDrumTimer = 15;
constexpr int maxDrumTimer = 25;

class DrumRotation : public Statements {
public:
	DrumRotation();
	void drawInterface(GameMachine* gameMachine) override;
	bool workIsUp() const override;
private:
	void compliteWork();
	bool finished;
	Timer drumTimer;
	Timer pause;
};

