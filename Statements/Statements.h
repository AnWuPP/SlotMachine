#pragma once

#include <memory>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class GameMachine;
class WaitingPlayerAction;
class DrumRotation;
class ShowPrize;

class Statements
{
public:
	virtual ~Statements() = default;
	virtual void drawInterface(GameMachine* gameMachine) = 0;
	virtual bool workIsUp() const = 0;
};