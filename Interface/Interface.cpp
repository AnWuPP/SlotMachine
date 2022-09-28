#include "Interface.h"

Interface::Interface() :	window(nullptr), buttonPressed(ButtonType::NONE),
							columnsCount(0) {
	if (!glfwInit())
		return;
	window = glfwCreateWindow(
		800,
		480,
		"Slot Machine",
		NULL,
		NULL
	);
	if (window == nullptr) {
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

Interface::~Interface() {
	glfwDestroyWindow(window);
	glfwTerminate();
}


bool Interface::windowOpened() const {
	return !glfwWindowShouldClose(window);
}

void Interface::shutdown() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Interface::loop(Statements* state, GameMachine* gameMachine)
{
	if (state == nullptr)
		throw std::runtime_error("Bad state pointer");
	if (gameMachine == nullptr)
		throw std::runtime_error("Bad GameMachine class pointer");
	buttonPressed = ButtonType::NONE;
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
	state->drawInterface(gameMachine);
	ImGui::EndChild();
		
	ImGui::SameLine();
	if (ImGui::Button("START", ImVec2(55.0f, 30.0f)))
	{
		buttonPressed = ButtonType::START;
	}
	ImGui::SameLine();
	if (ImGui::Button("STOP", ImVec2(55.0f, 30.0f)))
	{
		buttonPressed = ButtonType::STOP;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
	glfwPollEvents();
}