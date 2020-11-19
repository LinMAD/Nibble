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
		// TODO Improve this slow section

		if (dynamic_cast<WindowResizeEvent*>(&e) != nullptr)
			OnWindowResizeEvent(dynamic_cast<WindowResizeEvent&>(e));

		if (dynamic_cast<MouseButtonPressedEvent*>(&e) != nullptr)
		{
			OnMouseButtonPressedEvent(dynamic_cast<MouseButtonPressedEvent&>(e));
			e.SetIsHandled();
		}

		if (dynamic_cast<MouseButtonReleasedEvent*>(&e) != nullptr)
		{
			OnMouseButtonReleasedEvent(dynamic_cast<MouseButtonReleasedEvent&>(e));
			e.SetIsHandled();
		}

		if (dynamic_cast<MouseMovedEvent*>(&e) != nullptr)
		{
			OnMouseMovedEvent(dynamic_cast<MouseMovedEvent&>(e));
			e.SetIsHandled();
		}

		if (dynamic_cast<MouseScrolledEvent*>(&e) != nullptr)
		{
			OnMouseScrolledEvent(dynamic_cast<MouseScrolledEvent&>(e));
			e.SetIsHandled();
		}
	}

	void GuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

		glViewport(0, 0, e.GetWidth(), e.GetHeight());
	}

	void GuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
	}

	void GuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
	}

	void GuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());
	}

	void GuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();
	}
}
