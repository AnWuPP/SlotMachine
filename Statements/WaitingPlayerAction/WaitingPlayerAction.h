#pragma once
#include "../Statements.h"
class WaitingPlayerAction : public Statements {
public:
	WaitingPlayerAction();
	void drawInterface() const override;
	bool workIsUp() const override;
private:
	bool stateFinished;
};

