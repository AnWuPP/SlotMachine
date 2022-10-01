#pragma once

#include "../Statements.h"

class ShowPrize : public Statements {
public:
	ShowPrize();
	void drawInterface(GameMachine* gameMachine) override;
	bool workIsUp() const override;
private:
	bool finished;
};

