#include "pch.h"
#include "Core/Application.h"
#include "Traceability/Logger.h"
#include "Events/EventBus.h"
#include "Events/Window/WindowEvent.h"
#include <GLFW/glfw3.h>

Nibble::Application::Application()
{
	WinWindow window;
	m_window = std::unique_ptr<IWindow>(window.Create());
}

Nibble::Application::~Application()
{
}

void Nibble::Application::Run()
{
	LOGGER_APP_INFO("Initializing");
	EventBus eventBus;
	// TODO Add EventHandler for contrect events

	WindowResizeEvent eWinResize(1280, 720);
	if (eWinResize.IsInCategory(EventCategory::Window))
		LOGGER_APP_INFO(eWinResize.ToString());

	// Main loop for updates
	while (m_running)
	{
		// TODO Update EventHandler window, keyboard, mouse etc
		eventBus.Notify();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		m_window->OnUpdate();
	}
}