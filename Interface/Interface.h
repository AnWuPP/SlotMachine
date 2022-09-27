#pragma once
#include <vector>
#include <stdexcept>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_custom_figure.h"
#include <GLFW/glfw3.h>
#include "../Statements/Statements.h"

enum class ButtonType {
	NONE = 0,
	START,
	STOP
};

class Interface {
public:
	ButtonType buttonPressed;
	Interface();
	~Interface();
	void loop(Statements* state);
	bool windowOpened() const;
	void shutdown();
private:
	GLFWwindow* window;
	size_t columnsCount;
};

