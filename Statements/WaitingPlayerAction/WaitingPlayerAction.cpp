#include "WaitingPlayerAction.h"
#include "../../GameMachine/GameMachine.h"

WaitingPlayerAction::WaitingPlayerAction() : finished(true) { }

void WaitingPlayerAction::drawInterface(GameMachine* gameMachine) {
	if (gameMachine == nullptr)
		throw std::runtime_error("Bad GameMachine class pointer");
	auto& fList = gameMachine->getFigureList();
	int id = 0;
	auto draw = [&](auto& e) {
		gameMachine->getInterface().drumPainter(id, e, false);
		ImGui::NextColumn();
		++id;
	};
	std::for_each(fList.begin(), fList.end(), draw);
}

bool WaitingPlayerAction::workIsUp() const {
	return finished;
}