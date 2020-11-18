#include "pch.h"
#include "WinWindow.h"
#include "Event/Window/WindowResizeEvent.h"
#include "Event/Window/WindowsCloseEvent.h"
#include "Event/Mouse/MouseButtonPressedEvent.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Nibble {
	static bool s_GlfwInitialized = false;
	static bool s_GladInitialized = false;

	static void GlfwErrorCallback(int error, const char* description)
	{
		M_LOGGER_ENG_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	void WinWindow::Init(const WindowConfiguration& cfg)
	{
		m_Data.Title = cfg.Title;
		m_Data.Width = cfg.Width;
		m_Data.Height = cfg.Height;

		M_LOGGER_ENG_DEBUG("Atempt to create window {0} ({1}, {2})", cfg.Title, cfg.Width, cfg.Height);

		if (!s_GlfwInitialized)
		{
			int success = glfwInit();

			NIBBLE_CORE_ASSERT(success, "GLFW intialize failed!");

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			glfwSetErrorCallback(GlfwErrorCallback);

			s_GlfwInitialized = true;
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

		if (!s_GladInitialized)
		{
			int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			NIBBLE_CORE_ASSERT(success, "Failed to initialize GLAD");

			s_GladInitialized = true;
		}

		// TODO Keyboard, Character events
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				if (action == GLFW_PRESS)
				{
					EVENT_BUS_ADD_EVENT(std::make_shared<MouseButtonPressedEvent>(button));
				}
				else if (action == GLFW_RELEASE)
				{
					M_LOGGER_ENG_INFO("Mouse release evente ->>>>");
				}
			}
		);
	}

	inline auto WinWindow::WindowResizeCallback(GLFWwindow* win, int w, int h) -> void
	{
		auto e = std::make_shared<WindowResizeEvent>(w, h);
		EVENT_BUS_ADD_EVENT(e);

		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
		data.Width = w;
		data.Height = h;

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
