#include "GameMachine.h"
#include "../Statements/WaitingPlayerAction/WaitingPlayerAction.h"

GameMachine::GameMachine() : state(nullptr) { }

std::shared_ptr<Statements> GameMachine::getState() const {
	return state;
}

void GameMachine::setState(std::shared_ptr<Statements> inState) {
	if (inState.get() == nullptr)
		throw std::runtime_error("Bad state pointer");
	if (state.get() != nullptr)
		state.reset();
	state = inState;
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
		std::generate(
			column.begin(),
			column.end(),
			random
		);
		return column;
	};

	figureList.resize(columnsCount);
	std::generate(
		figureList.begin(),
		figureList.end(),
		gen
	);
}

void GameMachine::process() {
	setState(std::make_shared<WaitingPlayerAction>());
	generateFigureList(columns);
	while (mainInterface.windowOpened()) {
		mainInterface.loop(state.get(), this);
	}
	mainInterface.shutdown();
}