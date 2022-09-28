#pragma once

#include <memory>
#include <GLFW/glfw3.h>
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
	virtual void drawInterface(GameMachine* gameMachine) const = 0;
};