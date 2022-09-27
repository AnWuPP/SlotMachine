#pragma once
#include <memory>
#include <vector>
#include <random>
#include "../Statements/Statements.h"
#include "../Interface/Interface.h"

constexpr size_t columns = 5; // default columns count
constexpr int figureCount = 4;

class GameMachine {
public:
	GameMachine();
	std::shared_ptr<Statements> getState() const;
	void setState(std::vector<std::shared_ptr<Statements>>& inQueue);
	void nextState();
	void process();
	std::vector<std::vector<int>>& getFigureList();
	void generateFigureList(size_t columns);
private:
	std::shared_ptr<Statements> state;
	std::vector<std::shared_ptr<Statements>> queue;
	Interface mainInterface;
	std::vector<std::vector<int>> figureList;
};

