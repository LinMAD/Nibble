#include "pch.h"
#include "Render/Platform/Win/WinWindow.h"

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
	}

	void WinWindow::Shutdown()
	{
		glfwDestroyWindow(m_window);
	}

	WinWindow::WinWindow()
	{
	}

	WinWindow::WinWindow(const WindowConfiguration& cfg)
	{
		Init(cfg);
	}

	WinWindow::~WinWindow()
	{
		Shutdown();
	}

	IWindow* WinWindow::Create(const WindowConfiguration& cfg)
	{
		return new WinWindow(cfg);
	}

	void WinWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
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