#pragma once

#include "../Statements.h"

class DrumRotation : public Statements {
public:
	DrumRotation();
	void drawInterface(GameMachine* gameMachine) const override;
};

