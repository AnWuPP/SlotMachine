#include "WaitingPlayerAction.h"
#include "../../GameMachine/GameMachine.h"

WaitingPlayerAction::WaitingPlayerAction() : finished(false) { }

void WaitingPlayerAction::drawInterface(GameMachine* gameMachine) {
	if (gameMachine == nullptr)
		throw std::runtime_error("Bad GameMachine class pointer");
	auto& fList = gameMachine->getFigureList();
	auto draw = [&](auto& e) {
		gameMachine->getInterface().drumPainter(e);
		ImGui::NextColumn();
	};
	std::for_each(fList.begin(), fList.end(), draw);
}

bool WaitingPlayerAction::workIsUp() const {
	return finished;
}

void WaitingPlayerAction::setFinished() {
	finished = true;
}