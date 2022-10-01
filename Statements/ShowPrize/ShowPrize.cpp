#include "ShowPrize.h"
#include "../../GameMachine/GameMachine.h"
#include "../WaitingPlayerAction/WaitingPlayerAction.h"

ShowPrize::ShowPrize() : finished(true) {
	timer.start(showTime);
}

void ShowPrize::drawInterface(GameMachine* gameMachine) {
	if (gameMachine == nullptr)
		throw std::runtime_error("Bad GameMachine class pointer");
	auto& fList = gameMachine->getFigureList();
	auto winSize = ImGui::GetWindowSize();
	auto width = ImGui::GetColumnWidth();
	const int offset = 12; // defailt offset for small screen, dont adaptive :C
	auto prize = [&, this](auto& e) {
		auto spos = ImGui::GetCursorPosX();
		ImGui::SetCursorPos(ImVec2(spos + width / 2.f - 30.f, winSize.x / 2.f - 140.f));
		switch (e[offset]) {
		case 1:
			ImGui::customRect();
			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::Text("200");
			break;
		case 2:
			ImGui::customTriangle();
			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::Text("300");
			break;
		case 3:
			ImGui::customLeaf();
			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::Text("400");
			break;
		default:
			ImGui::customCircle();
			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::Text("100");
			break;
		}
		ImGui::SetCursorPosX(spos);
		ImGui::NextColumn();
	};
	std::for_each(fList.begin(), fList.end(), prize);
	if (timer.isRunning() && timer.timeIsUp()) {
		gameMachine->setState(std::make_shared<WaitingPlayerAction>());
	}
}

bool ShowPrize::workIsUp() const {
	return finished;
}