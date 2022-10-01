#include "DrumRotation.h"
#include "../../GameMachine/GameMachine.h"

DrumRotation::DrumRotation() : finished(false) { }

void DrumRotation::drawInterface(GameMachine* gameMachine) {
}

bool DrumRotation::workIsUp() const {
	return finished;
}