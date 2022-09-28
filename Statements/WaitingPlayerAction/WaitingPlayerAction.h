#pragma once

#include "../Statements.h"

class GameMachine;
class DrumRotation;

class WaitingPlayerAction : public Statements {
public:
	WaitingPlayerAction();
	void drawInterface(GameMachine* gameMachine) const override;
private:
};

