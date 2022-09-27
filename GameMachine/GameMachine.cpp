#include "GameMachine.h"
#include <iostream>

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

void GameMachine::generateFigureList(size_t columnsCount) {
	if (!figureList.empty())
		figureList.clear();

	auto random = [] {
		std::random_device rd;
		std::uniform_int_distribution range(0, figureCount - 1);
		return range(rd);
	};

	auto gen = [&random]() {
		std::vector<int> column(figureOfColumn);
		std::generate(column.begin(), column.end(), random);
		return column;
	};

	figureList.resize(columnsCount);
	std::generate(
		std::make_move_iterator(figureList.begin()),
		std::make_move_iterator(figureList.end()),
		gen
	);
}

void GameMachine::process() {
	generateFigureList(columns);
	while (mainInterface.windowOpened()) {
		//mainInterface.loop(state.get());
	}
	mainInterface.shutdown();
}