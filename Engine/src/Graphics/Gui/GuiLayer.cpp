#include "pch.h"
#include "GuiLayer.h"
#include "Platform/OpenGL/ImGuiImplOpenGLRenderer.h"
#include "Core/Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace Nibble {
	GuiLayer::GuiLayer() : ILayer("GUI Layer")
	{
	}

	GuiLayer::~GuiLayer()
	{
	}

	void GuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsLight();

		ImGuiIO& io = ImGui::GetIO();
		// Mouse
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		// TODO Keyboard

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void GuiLayer::OnDetach()
	{
	}

	void GuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Engine& eng = Engine::GetInstance();
		io.DisplaySize = ImVec2(eng.GetWindow().GetWidth(), eng.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GuiLayer::OnEvent(Event& e)
	{
	}
}
