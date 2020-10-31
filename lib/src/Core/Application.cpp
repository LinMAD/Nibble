#include <GLFW/glfw3.h>

#include "pch.h"
#include "Core/Application.h"
#include "Traceability/Logger.h"
#include "Event/Window/WindowResizeEvent.h"

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

	// Main loop
	while (m_running)
	{
		EventBus& bus = Nibble::EventBus::GetInstance();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_window->OnUpdate();

		std::shared_ptr<Event> winClose = bus.DispatchEvent(Event::EventType::WindowClose);
		if (winClose != nullptr && winClose->IsHandled())
			break;

		bus.Process();
	}
}