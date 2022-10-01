#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include "imgui_custom_figure.h"

class DrumPainter {
public:
	DrumPainter();
	void operator()(std::vector<int>& drum);
private:
	float pos;
	const float step;
	const float maxSpeed;
};

