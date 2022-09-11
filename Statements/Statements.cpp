#include "Statements.h"

int WaitingPlayerActionStatements::get_id() const
{
	return 0;
}
void WaitingPlayerActionStatements::paint()
{
}

int ShowPrizeStatements::get_id() const
{
	return 1;
}
void ShowPrizeStatements::paint()
{
	ImGui::Text("State 1");
}

int DrumRotationStatements::get_id() const
{
	return 2;
}
void DrumRotationStatements::paint()
{
	ImGui::Text("State 2");
}