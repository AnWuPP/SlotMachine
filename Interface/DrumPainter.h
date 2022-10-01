#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include <map>
#include "imgui_custom_figure.h"

constexpr int maxFigureColumn = 100; // set figure of one column

class DrumPainter {
public:
	DrumPainter();
	void operator()(int id, std::vector<int>& drum, bool moveble, float timeComplite = 0.f);
private:
	float pos;
	const float step;
	const float maxSpeed;
	std::unordered_map<int, float> offset;
};

