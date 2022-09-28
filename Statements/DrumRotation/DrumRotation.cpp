#include "DrumRotation.h"
#include "../../GameMachine/GameMachine.h"

DrumRotation::DrumRotation() { }

void DrumRotation::drawInterface(GameMachine* gameMachine) const {
	gameMachine->setState(std::make_shared<DrumRotation>());
}