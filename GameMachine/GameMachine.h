#pragma once
#include <memory>
#include <vector>
#include "../Statements/Statements.h"
#include "../Interface/Interface.h"

class GameMachine
{
public:
	GameMachine(Interface& interface);
	std::shared_ptr<Statements> get_state() const;
	void set_state(std::vector<std::shared_ptr<Statements>>& queue);
	void next_state();
	void process();
private:
	std::shared_ptr<Statements> _state;
	std::vector<std::shared_ptr<Statements>> _queue;
	std::shared_ptr<Interface> _interface;
};

