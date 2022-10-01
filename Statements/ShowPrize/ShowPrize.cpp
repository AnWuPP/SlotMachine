#include "ShowPrize.h"
#include "../../GameMachine/GameMachine.h"

ShowPrize::ShowPrize() : finished(false) { }

void ShowPrize::drawInterface(GameMachine* gameMachine) {
}

bool ShowPrize::workIsUp() const {
	return finished;
}