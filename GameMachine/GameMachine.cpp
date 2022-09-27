#include "GameMachine.h"

GameMachine::GameMachine() : state(nullptr) { }

std::shared_ptr<Statements> GameMachine::getState() const {
	return state;
}

void GameMachine::setState(std::vector<std::shared_ptr<Statements>>& inQueue) {
	if (inQueue.empty() || !queue.empty()) {
		return;
	}
	queue = inQueue;
	state = queue[0];
}

void GameMachine::nextState() {
	if (queue.empty()) {
		return;
	}
	auto it = std::find(queue.begin(), queue.end(), state);
	if (it == queue.end()) {
		return;
	}
	if (++it == queue.end()) {
		it = queue.begin();
	}
	state = *it;
}

std::vector<std::vector<int>>& GameMachine::getFigureList() {
	return figureList;
}

void GameMachine::generateFigureList(size_t columns) {
	if (!figureList.empty())
		figureList.clear();
	for (size_t i = 0; i != columns; ++i) {

	}
}

void GameMachine::process() {
	while (mainInterface.windowOpened()) {
		mainInterface.loop(state.get());
	}
	mainInterface.shutdown();
}