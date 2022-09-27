#pragma once

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Statements
{
public:
	virtual ~Statements() = default;
	virtual void drawInterface() const = 0;
	virtual bool workIsUp() const = 0;
};