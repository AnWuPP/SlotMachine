#include "DrumRotation.h"
#include "../../GameMachine/GameMachine.h"
#include "../ShowPrize/ShowPrize.h"

DrumRotation::DrumRotation() : finished(false) {
	pause.start(pauseTime);
}

void DrumRotation::drawInterface(GameMachine* gameMachine) {
	if (gameMachine == nullptr)
		throw std::runtime_error("Bad GameMachine class pointer");
	if (pause.isRunning() && pause.timeIsUp())
		pause.stop();
	auto& fList = gameMachine->getFigureList();
	int id = 0;
	bool animate = drumTimer.isRunning() && !drumTimer.timeIsUp();
	if (!animate && !pause.isRunning()) {
		auto random = [] {
			std::random_device rd;
			std::uniform_int_distribution range(minDrumTimer, maxDrumTimer);
			return range(rd);
		};
		drumTimer.start(random());
	}
	float complite = drumTimer.complite() >= 0.5f ? 1.0f - drumTimer.complite() : drumTimer.complite();
	auto draw = [&](auto& e) {
		gameMachine->getInterface().drumPainter(id, e, animate, complite);
		ImGui::NextColumn();
		++id;
	};
	std::for_each(fList.begin(), fList.end(), draw);
	if (drumTimer.timeIsUp()) {
		if (!pause.isRunning())
			pause.start(pauseTime);
		if (pause.isRunning() && pause.timeIsUp())
			gameMachine->setState(std::make_shared<ShowPrize>());
	}
}

bool DrumRotation::workIsUp() const {
	return finished;
}

void DrumRotation::compliteWork() {
	finished = true;
}