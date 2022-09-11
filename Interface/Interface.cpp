#include "Interface.h"

Interface::Interface() : _window(nullptr),
						pressed_button(ButtonType::NONE),
						events(Events::NONE),
						_draws({
							&Interface::draw_triangle,
							&Interface::draw_circle,
							&Interface::draw_rect,
							&Interface::draw_leaf
							}),
						_prize_size({
							100,
							200,
							300,
							400
							}),
						_draw_size(60.f),
						_animate(false),
						_timer(),
						_stopping_animate(false)
{
	if (!glfwInit())
		return;
	_window = glfwCreateWindow(
		800,
		480,
		"Slot Machine",
		NULL,
		NULL
	);
	if (_window == nullptr)
	{
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(_window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	generate_columns(5);
}

Interface::~Interface()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void Interface::draw_triangle()
{
	auto draw_list = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetCursorScreenPos();
	draw_list->AddTriangleFilled(
							ImVec2(pos.x, pos.y + _draw_size),
							ImVec2(pos.x + _draw_size / 2.f, pos.y),
							ImVec2(pos.x + _draw_size, pos.y + _draw_size),
							ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f))
						);
}

void Interface::draw_rect()
{
	auto draw_list = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetCursorScreenPos();
	draw_list->AddRectFilled(
		pos,
		ImVec2(pos.x + _draw_size, pos.y + _draw_size),
		ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f))
	);
}

void Interface::draw_circle()
{
	auto draw_list = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetCursorScreenPos();
	draw_list->AddCircleFilled(
		ImVec2(pos.x + _draw_size / 2.f, pos.y + _draw_size / 2.f),
		_draw_size / 2.f,
		ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f))
	);
}

void Interface::draw_leaf()
{
	auto draw_list = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetCursorScreenPos();
	draw_list->AddRectFilled(pos, ImVec2(pos.x + _draw_size, pos.y + _draw_size),
		ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f)),
		20.f, ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersBottomRight);
}

bool Interface::is_window_open()
{
	return !glfwWindowShouldClose(_window);
}

void Interface::shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Interface::go_animate()
{
	std::random_device rd;
	std::uniform_int_distribution<int> dist(10, 20);
	int random = dist(rd);
	_timer.start(random);
	_animate = true;
	_stopping_animate = false;
}

std::vector<int> Interface::get_wons()
{
	return _wons_list;
}

void Interface::stopping_animate()
{
	_stopping_animate = true;
}

void Interface::generate_columns(int count)
{
	std::vector<int> to_cols;
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, static_cast<int>(_draws.size()) - 1);
	const int count_figure = 40;
	for (size_t i = 0, ie = count; i != ie; ++i)
	{
		for (size_t j = 0; j < count_figure; ++j)
		{
			to_cols.push_back(dist(rd));
		}
		_columns.push_back(to_cols);
		to_cols.clear();
		_anim_pos.push_back(0.f);
		_wons_list.push_back(-1);
	}
}

void Interface::draw_column(int id, float delta, float max_speed)
{
	if (id > _columns.size() - 1)
		return;
	const auto p = ImGui::GetCursorScreenPos();
	float step = delta;
	if (_timer.complite() == 0.f)
		step = max_speed * .1f;
	float y = p.y - (_draw_size * 4.f);
	if (_animate)
	{
		_anim_pos[id] += step;
		if (_anim_pos[id] >= _draw_size + _draw_size / 2.f + step / 2.f)
		{
			int e = _columns[id][_columns[id].size() - 1];
			int s = _columns[id][0];
			_columns[id][0] = e;
			for (int i = 1, ie = static_cast<int>(_columns[id].size()) - 1; i != ie; ++i)
			{
				int temp = _columns[id][i + 1];
				_columns[id][i + 1] = s;
				s = temp;
			}
			_anim_pos[id] = 0;
			if (_stopping_animate && id == _columns.size() - 1)
			{
				std::transform(_anim_pos.begin(), _anim_pos.end(), _anim_pos.begin(), [](auto a)
					{
						return 0.f;
					});
				_timer.stop();
				_animate = false;
				_stopping_animate = false;
				pressed_button = ButtonType::STOP;
			}
		}
	}
	y += _anim_pos[id];
	for (int i = 0, ie = static_cast<int>(_columns[id].size()); i != ie; ++i)
	{
		ImGui::SetCursorScreenPos(ImVec2(p.x, y));
		_draws[_columns[id][i]](this);
		const auto win_size = ImGui::GetWindowSize();
		if (y > (win_size.y / 2 - _draw_size * 2.f) && y < (win_size.y / 2 - _draw_size * 2.f) + 20.f)
			_wons_list[id] = _columns[id][i];
		y += _draw_size + _draw_size / 2.f;
	}

	if (_animate && _timer.running && _timer.time_is_up() && id == _columns.size() - 1)
	{
		stopping_animate();
	}
}

void Interface::show_prize(int id)
{
	const auto win_size = ImGui::GetWindowSize();
	ImGui::SetCursorPosY(win_size.y / 2.f - _draw_size);
	auto e = _wons_list[id];
	_draws[e](this);
	ImGui::SetCursorPosY(win_size.y / 2.f + _draw_size / 2.f);
	ImGui::Text("%d", _prize_size[e]);
}

void Interface::state_paint(int id)
{
	if (id == 1)
	{
		if (!_prize_timer.running)
			_prize_timer.start(5);
		if (_prize_timer.time_is_up())
		{
			events = Events::PRIZE_SHOWED;
			_prize_timer.stop();
		}
	}
	const auto size = static_cast<int>(_columns.size());
	ImGui::Columns(size, "cols", false);
	const float max_speed = 40.f;
	float delta = (_timer.complite() < 0.5 ? max_speed * _timer.complite() : max_speed * (1.f - _timer.complite()));
	for (int i = 0, ie = size; i != ie; ++i)
	{
		const auto width = ImGui::GetColumnWidth();
		const auto x = ImGui::GetCursorPosX();
		ImGui::SetCursorPosX(x + (width / 4.f));
		if (id == 1)
			show_prize(i);
		else
			draw_column(i, delta, max_speed);
		ImGui::SetCursorPosY(0);
		ImGui::NextColumn();
	}
	ImGui::Columns();
}

void Interface::loop(Statements* paint)
{
	pressed_button = ButtonType::NONE;
	events = Events::NONE;
	glClearColor(.0f, .0f, .0f, .0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::Begin("##MainWindow", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::BeginChild("##Scrollbar", ImVec2(viewport->WorkSize.x - 150.f, .0f), true);
	state_paint(paint->get_id());
	ImGui::EndChild();
		
	ImGui::SameLine();
	if (ImGui::Button("START", ImVec2(55.0f, 30.0f)))
	{
		pressed_button = ButtonType::START;
	}
	ImGui::SameLine();
	if (ImGui::Button("STOP", ImVec2(55.0f, 30.0f)))
	{
		pressed_button = ButtonType::STOP;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(_window);
	glfwPollEvents();
}