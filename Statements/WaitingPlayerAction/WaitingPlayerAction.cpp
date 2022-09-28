#include "WaitingPlayerAction.h"
#include "../../GameMachine/GameMachine.h"
#include "../DrumRotation/DrumRotation.h"

WaitingPlayerAction::WaitingPlayerAction() { }

void WaitingPlayerAction::drawInterface(GameMachine* gameMachine) const {
	//gameMachine->setState(std::make_shared<DrumRotation>());
}
