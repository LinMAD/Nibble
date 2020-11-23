#include "pch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "GuiLayer.h"
#include "Core/Engine.h"

namespace Nibble {
	GuiLayer::GuiLayer() : ILayer("GUI Layer")
	{
	}

	GuiLayer::~GuiLayer()
	{
	}

	void GuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsClassic();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Engine& eng = Engine::GetInstance();
		GLFWwindow* window = static_cast<GLFWwindow*>(eng.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void GuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void GuiLayer::OnGuiUpdate()
	{
		
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Custom window");
			ImGui::Text("This is some useful text.");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

			if (ImGui::Button("Button")) counter++;

			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGuiStyle& style = ImGui::GetStyle();
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			ImGui::End();
		}
	}

	void GuiLayer::BiginFrameRender()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void GuiLayer::EndFrameRender()
	{
		ImGuiIO& io = ImGui::GetIO();
		Engine& eng = Engine::GetInstance();
		io.DisplaySize = ImVec2(
			(float)eng.GetWindow().GetWidth(), 
			(float)eng.GetWindow().GetHeight()
		);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
