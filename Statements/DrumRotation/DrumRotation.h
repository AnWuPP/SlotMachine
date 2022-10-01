#pragma once

#include "../Statements.h"

class DrumRotation : public Statements {
public:
	DrumRotation();
	void drawInterface(GameMachine* gameMachine) override;
	bool workIsUp() const override;
private:
	bool finished;
};

