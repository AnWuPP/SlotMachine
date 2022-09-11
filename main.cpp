#include <iostream>
#include "GameMachine/GameMachine.h"

int main()
{
	std::vector<std::shared_ptr<Statements>> states_queue {
		std::make_shared<WaitingPlayerActionStatements>(),
		std::make_shared<DrumRotationStatements>(),
		std::make_shared<ShowPrizeStatements>()
	};

	Interface interface;

	GameMachine game_machine(interface);
	game_machine.set_state(states_queue);

	game_machine.process();

}