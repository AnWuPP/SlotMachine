#include "DrumPainter.h"

DrumPainter::DrumPainter() : step(20.f), maxSpeed(60.f), pos(-800.f) { }

void DrumPainter::operator()(int id, std::vector<int>& drum, bool moveble, float timeComplite) {
	if (offset.find(id) == offset.end()) {
		offset[id] = 0.f;
	}
	if (moveble)
		offset[id] += maxSpeed * timeComplite;
	auto column = [this, &id](int& element) {
		auto spos = ImGui::GetCursorPosX();
		auto width = ImGui::GetColumnWidth();
		ImGui::SetCursorScreenPos(ImVec2(spos + width / 2.f - drawSize / 2.f, pos + offset[id]));
		switch (element) {
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
	if (moveble) {
		if (offset[id] >= step + drawSize) {
			drum.insert(drum.begin(), *(--drum.end()));
			drum.erase(--drum.end());
			offset[id] = 0.f;
		}
	}
	pos = -800.f;
}