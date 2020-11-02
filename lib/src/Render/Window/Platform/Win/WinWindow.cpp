#include "pch.h"
#include "Render/Window/Platform/Win/WinWindow.h"
#include "Event/Window/WindowResizeEvent.h"
#include "Event/Window/WindowsCloseEvent.h"

namespace Nibble {
	static bool s_GLFWInitialized = false;

	void WinWindow::Init(const WindowConfiguration& cfg)
	{
		m_Data.Title = cfg.Title;
		m_Data.Width = cfg.Width;
		m_Data.Height = cfg.Height;

		LOGGER_CORE_INFO("Atempt to create window {0} ({1}, {2})", cfg.Title, cfg.Width, cfg.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			NIBBLE_CORE_ASSERT(success, "GLFW intialize failed!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(
			(int)cfg.Width,
			(int)cfg.Height,
			m_Data.Title.c_str(),
			nullptr,
			nullptr
		);

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, WindowResizeCallback);
		glfwSetWindowCloseCallback(m_Window, WindowCloseCallback);
	}

	inline auto WinWindow::WindowResizeCallback(GLFWwindow* win, int w, int h) -> void
	{
		auto e = std::make_shared<WindowResizeEvent>(w, h);
		EVENT_BUS_ADD_EVENT(e);

		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);

		e->SetIsHandled();
	}

	inline auto WinWindow::WindowCloseCallback(GLFWwindow* win) -> void
	{
		WinWindow& winWindow = *(WinWindow*)glfwGetWindowUserPointer(win);

		if (!winWindow.m_IsPossibleCloseWindow) return;

		glfwSetWindowShouldClose(win, GLFW_TRUE);

		EVENT_BUS_ADD_EVENT(std::make_shared<WindowsCloseEvent>());
	}

	WinWindow::WinWindow(const WindowConfiguration& cfg)
	{
		Init(cfg);
	}

	WinWindow::~WinWindow()
	{
		glfwDestroyWindow(m_Window);
	}

	IWindow* WinWindow::Create(const WindowConfiguration& cfg)
	{
		return new WinWindow(cfg);
	}

	void WinWindow::OnUpdate()
	{
		if (glfwWindowShouldClose(m_Window)) return;

		glfwPollEvents();
		glfwSwapBuffers(m_Window);

		m_IsPossibleCloseWindow = false;

		std::shared_ptr<Event> winClose = Nibble::EventBus::GetInstance().DispatchEvent(Event::EventType::WindowClose);
		if (winClose != nullptr)
			winClose->SetIsHandled();
	}

	void WinWindow::SetVSync(bool enabled)
	{
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WinWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}