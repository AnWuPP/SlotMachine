#pragma once
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
class Statements
{
public:
	typename typedef Statements type_t;
	using type = Statements;
	virtual ~Statements() = default;

	virtual int get_id() const = 0;
	virtual void paint() = 0;
};

class WaitingPlayerActionStatements : public Statements
{
public:
	typename typedef WaitingPlayerActionStatements type_t;
	using type = WaitingPlayerActionStatements;
	int get_id() const override;
	void paint() override;
};

class ShowPrizeStatements : public Statements
{
public:
	using type = ShowPrizeStatements;
	int get_id() const override;
	void paint() override;
};

class DrumRotationStatements : public Statements
{
public:
	using type = ShowPrizeStatements;
	int get_id() const override;
	void paint() override;
};

