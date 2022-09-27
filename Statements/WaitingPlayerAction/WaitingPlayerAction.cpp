#include "WaitingPlayerAction.h"

WaitingPlayerAction::WaitingPlayerAction() : stateFinished(false) { }

bool WaitingPlayerAction::workIsUp() const {
	return stateFinished;
}

void WaitingPlayerAction::drawInterface() const {

}
