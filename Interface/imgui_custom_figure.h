#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

constexpr auto drawSize = 60.f;

namespace ImGui {
	void customTriangle();
	void customRect();
	void customCircle();
	void customLeaf();
}