#include "pch.h"
#include "Render/Window/Platform/Win/WinWindow.h"
#include "Event/Window/WindowResizeEvent.h"
#include "Event/Window/WindowsCloseEvent.h"

namespace Nibble {
	static bool s_GLFWInitialized = false;

	void WinWindow::Init(const WindowConfiguration& cfg)
	{
		m_data.Title = cfg.Title;
		m_data.Width = cfg.Width;
		m_data.Height = cfg.Height;

		LOGGER_CORE_INFO("Atempt to create window {0} ({1}, {2})", cfg.Title, cfg.Width, cfg.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			NIBBLE_CORE_ASSERT(success, "GLFW intialize failed!");

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow(
			(int)cfg.Width,
			(int)cfg.Height,
			m_data.Title.c_str(),
			nullptr,
			nullptr
		);

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_window, WindowResizeCallback);
		glfwSetWindowCloseCallback(m_window, WindowCloseCallback);
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

		if (!winWindow.m_isPossibleCloseWindow) return;

		glfwDestroyWindow(win);

		EVENT_BUS_ADD_EVENT(std::make_shared<WindowsCloseEvent>());
	}

	WinWindow::WinWindow(const WindowConfiguration& cfg)
	{
		Init(cfg);
	}

	IWindow* WinWindow::Create(const WindowConfiguration& cfg)
	{
		return new WinWindow(cfg);
	}

	void WinWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);

		if (!glfwWindowShouldClose(m_window)) return;

		m_isPossibleCloseWindow = false;

		std::shared_ptr<Event> winClose = Nibble::EventBus::GetInstance().DispatchEvent(Event::EventType::WindowClose);
		if (winClose != nullptr)
			winClose->SetIsHandled();
	}

	void WinWindow::SetVSync(bool enabled)
	{
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		m_data.VSync = enabled;
	}

	bool WinWindow::IsVSync() const
	{
		return m_data.VSync;
	}
}