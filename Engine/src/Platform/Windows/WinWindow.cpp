#include "pch.h"
#include "WinWindow.h"
#include "Event/Window/WindowResizeEvent.h"
#include "Event/Window/WindowCloseEvent.h"
#include "Event/Mouse/MouseButtonPressedEvent.h"
#include "Event/Mouse/MouseButtonReleasedEvent.h"
#include "Event/Mouse/MouseMovedEvent.h"
#include "Event/Mouse/MouseScrolledEvent.h"
#include "Event/Keyboard/KeyPressedEvent.h"
#include "Event/Keyboard/KeyReleasedEvent.h"
#include "Event/Keyboard/KeyTypedEvent.h"

namespace Nibble {
	static bool s_GlfwInitialized = false;

	void WinWindow::Init(const WindowConfiguration& cfg)
	{
		m_Data.Title = cfg.Title;
		m_Data.Width = cfg.Width;
		m_Data.Height = cfg.Height;

		M_LOGGER_ENG_DEBUG("Atempt to create window {0} ({1}, {2})", cfg.Title, cfg.Width, cfg.Height);

		if (!s_GlfwInitialized)
		{
			int state = glfwInit();
			M_NIBBLE_ENG_ASSERT(state, "GLFW intialize failed!");
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

		m_GraphicsContext = new OpenGLContext(m_Window);
		m_GraphicsContext->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(m_Data.VSync);

		// WINDOW
		glfwSetWindowSizeCallback(m_Window, WindowResizeCallback);
		glfwSetWindowCloseCallback(m_Window, WindowCloseCallback);

		// MOUSE
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
		glfwSetCursorPosCallback(m_Window, MouseCursorPostionCallback);
		glfwSetScrollCallback(m_Window, MouseScrollPostionCallback);

		// KEYBOAD
		glfwSetKeyCallback(m_Window, KeyButtonCallback);
		glfwSetCharCallback(m_Window, KeyCharacterCallback);
	}

	inline auto WinWindow::GlfwErrorCallback(int error, const char* description) -> void
	{
		M_LOGGER_ENG_ERROR("GLFW Error ({0}): {1}", error, description);
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
	// TODO Events not handled yet
	inline auto WinWindow::WindowCloseCallback(GLFWwindow* win) -> void
	{
		WinWindow& winWindow = *(WinWindow*)glfwGetWindowUserPointer(win);

		glfwSetWindowShouldClose(win, GLFW_TRUE);

		EVENT_BUS_ADD_EVENT(std::make_shared<WindowsCloseEvent>());
	}

	inline auto WinWindow::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) -> void
	{
		if (action == GLFW_PRESS)
		{
			EVENT_BUS_ADD_EVENT(std::make_shared<MouseButtonPressedEvent>(button));
		}
		else if (action == GLFW_RELEASE)
		{
			EVENT_BUS_ADD_EVENT(std::make_shared<MouseButtonReleasedEvent>(button));
		}
	}

	inline auto WinWindow::MouseCursorPostionCallback(GLFWwindow* window, double xPos, double yPos) -> void
	{
		EVENT_BUS_ADD_EVENT(std::make_shared<MouseMovedEvent>(xPos, yPos));
	}

	inline auto WinWindow::MouseScrollPostionCallback(GLFWwindow* window, double xOffset, double yOffset) -> void
	{
		EVENT_BUS_ADD_EVENT(std::make_shared<MouseScrolledEvent>(xOffset, yOffset));
	}

	inline auto WinWindow::KeyButtonCallback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void
	{
		switch (action)
		{
			case GLFW_PRESS:
			{
				EVENT_BUS_ADD_EVENT(std::make_shared<KeyPressedEvent>(key, 0));
				break;
			}
			case GLFW_RELEASE:
			{
				EVENT_BUS_ADD_EVENT(std::make_shared<KeyReleasedEvent>(key));
				break;
			}
			case GLFW_REPEAT:
			{
				EVENT_BUS_ADD_EVENT(std::make_shared<KeyPressedEvent>(key, 1));
				break;
			}
		}
	}

	inline auto WinWindow::KeyCharacterCallback(GLFWwindow* window, unsigned int keycode) -> void
	{
		EVENT_BUS_ADD_EVENT(std::make_shared<KeyTypedEvent>(keycode));
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
		m_GraphicsContext->SwapBuffers();

		std::shared_ptr<Event> winClose = Nibble::EventBus::GetInstance().DispatchEvent(Event::EventType::WindowClose);
		if (winClose != nullptr) winClose->SetIsHandled();
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
