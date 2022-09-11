#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <memory>
#include <functional>
#include <random>
#include <string>
#include <chrono>
#include <GLFW/glfw3.h>
#include "../Statements/Statements.h"
#include <iostream>

enum class ButtonType
{
	NONE = 0,
	START,
	STOP
};

enum class Events
{
	NONE = 0,
	PRIZE_SHOWED
};

struct Timer
{
public:
	Timer();
	void start(int time);
	void stop();
	bool time_is_up();
	std::chrono::seconds difference();
	bool running;
	float complite();
private:
	std::chrono::time_point<std::chrono::system_clock> _start;
	std::chrono::time_point<std::chrono::system_clock> _end;
	std::chrono::seconds _time;
};

class Interface
{
public:
	ButtonType pressed_button;
	Events events;
	Interface();
	~Interface();
	void loop(Statements* paint);
	void state_paint(int id);
	bool is_window_open();
	void shutdown();
	void draw_triangle();
	void draw_rect();
	void draw_circle();
	void draw_leaf();
	void draw_column(int id, float delta, float max_speed);
	void generate_columns(int count);
	void go_animate();
	void stopping_animate();
	std::vector<int> get_wons();
	void show_prize(int id);
private:
	GLFWwindow* _window;
	std::vector<std::vector<int>> _columns;
	std::vector<int> _wons_list;

	std::vector<std::function<void(Interface*)>> _draws;
	const float _draw_size;

	bool _animate;
	bool _stopping_animate;
	std::vector<float> _anim_pos;
	Timer _timer;

	std::vector<int> _prize_size;
	Timer _prize_timer;
};

