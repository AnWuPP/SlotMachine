#include "imgui_custom_figure.h"

void ImGui::customTriangle()
{
	auto drawList = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetCursorScreenPos();
	drawList->AddTriangleFilled(
		ImVec2(pos.x, pos.y + drawSize),
		ImVec2(pos.x + drawSize / 2.f, pos.y),
		ImVec2(pos.x + drawSize, pos.y + drawSize),
		ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f))
	);
}

void ImGui::customRect()
{
	auto drawList = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetCursorScreenPos();
	drawList->AddRectFilled(
		pos,
		ImVec2(pos.x + drawSize, pos.y + drawSize),
		ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f))
	);
}

void ImGui::customCircle()
{
	auto drawList = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetCursorScreenPos();
	drawList->AddCircleFilled(
		ImVec2(pos.x + drawSize / 2.f, pos.y + drawSize / 2.f),
		drawSize / 2.f,
		ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f))
	);
}

void ImGui::customLeaf()
{
	auto drawList = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetCursorScreenPos();
	drawList->AddRectFilled(pos, ImVec2(pos.x + drawSize, pos.y + drawSize),
		ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f)),
		20.f, ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersBottomRight);
}
