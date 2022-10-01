#include "DrumPainter.h"

DrumPainter::DrumPainter() : pos(-800.f), step(20.f), maxSpeed(200.f) { }

void DrumPainter::operator()(std::vector<int>& drum) {
	auto column = [this](int& id) {
		auto spos = ImGui::GetCursorPosX();
		auto width = ImGui::GetColumnWidth();
		ImGui::SetCursorScreenPos(ImVec2(spos + width / 2.f - drawSize / 2.f, pos));
		switch (id) {
		case 1:
			ImGui::customRect();
			break;
		case 2:
			ImGui::customTriangle();
			break;
		case 3:
			ImGui::customLeaf();
			break;
		default:
			ImGui::customCircle();
			break;
		}
		pos += step + drawSize;
		ImGui::SetCursorPosX(spos);
	};
	std::for_each(drum.begin(), drum.end(), column);
	ImGui::SetCursorScreenPos(ImVec2(0, 0));
	pos = -800.f;
}