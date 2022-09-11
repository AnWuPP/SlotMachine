#include <iostream>
#include "GameMachine/GameMachine.h"

int main()
{
	std::shared_ptr<Statements> wait_player_state = std::make_shared<WaitingPlayerActionStatements>();
	std::shared_ptr<Statements> show_prize_state = std::make_shared<ShowPrizeStatements>();
	std::shared_ptr<Statements> drum_ratetion_state = std::make_shared<DrumRotationStatements>();
	std::vector<std::shared_ptr<Statements>> states_queue { wait_player_state, drum_ratetion_state, show_prize_state };

	Interface interface;

	GameMachine game_machine(interface);
	game_machine.set_state(states_queue);

	game_machine.process();

}