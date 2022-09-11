#pragma once
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
class Statements
{
public:
	virtual ~Statements() = default;

	virtual int get_id() const = 0;
};

class WaitingPlayerActionStatements : public Statements
{
public:
	int get_id() const override;
};

class ShowPrizeStatements : public Statements
{
public:
	int get_id() const override;
};

class DrumRotationStatements : public Statements
{
public:
	int get_id() const override;
};

