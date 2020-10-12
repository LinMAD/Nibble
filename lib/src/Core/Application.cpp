#include "pch.h"
#include "Core/Application.h"
#include "Traceability/Logger.h"
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
	// TODO Add EventHandler for contrect events

	// Main loop for updates
	while (m_running && !m_window->IsShootdown())
	{
		// TODO Update EventHandler window, keyboard, mouse etc

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_window->OnUpdate();
	}
}