#include "GameMachine.h"

GameMachine::GameMachine(Interface& interface) : _state(nullptr), _interface(std::make_shared<Interface>(interface)) { }

std::shared_ptr<Statements> GameMachine::get_state() const
{
	return _state;
}

void GameMachine::set_state(std::vector<std::shared_ptr<Statements>>& queue)
{
	if (queue.empty() || !_queue.empty())
	{
		return;
	}
	_queue = queue;
	_state = _queue[0];
}

void GameMachine::next_state()
{
	if (_queue.empty())
	{
		return;
	}
	auto it = std::find(_queue.begin(), _queue.end(), _state);
	if (it == _queue.end())
	{
		return;
	}
	if (++it == _queue.end())
	{
		it = _queue.begin();
	}
	_state = *it;
}

void GameMachine::process()
{
	while (_interface->is_window_open())
	{
		this->_interface->loop(this->_state.get());

		switch (_interface->pressed_button)
		{
			case ButtonType::START:
				if (_state->get_id() == 0)
				{
					this->next_state();
					_interface->go_animate();
				}
				break;
			case ButtonType::STOP:
				if (_state->get_id() == 2)
				{
					this->next_state();
					_interface->stopping_animate();
				}
				break;
			default:
				break;
		}
		if (_state->get_id() == 1 && _interface->events == Events::PRIZE_SHOWED)
		{
			this->next_state();
		}
	}
	_interface->shutdown();
}