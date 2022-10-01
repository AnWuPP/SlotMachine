#pragma once

#include "../Statements.h"
#include "../../Timer/Timer.h"

constexpr int showTime = 10;

class ShowPrize : public Statements {
public:
	ShowPrize();
	void drawInterface(GameMachine* gameMachine) override;
	bool workIsUp() const override;
private:
	bool finished;
	Timer timer;
};

