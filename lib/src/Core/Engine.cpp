#include <GLFW/glfw3.h>

#include "pch.h"
#include "Core/Engine.h"
#include "Traceability/Logger.h"

Nibble::Engine::Engine()
{
	WinWindow window;
	m_window = std::unique_ptr<IWindow>(window.Create());
}

void Nibble::Engine::PushLayer(std::shared_ptr<Layer> l)
{
	m_LayerStack.PushLayer(l);
}

void Nibble::Engine::PushOverlay(std::shared_ptr<Layer> ol)
{
	m_LayerStack.PushOverlay(ol);
}

void Nibble::Engine::Run()
{
	M_LOGGER_ENG_DEBUG("Executing main loop...");
	EventBus& bus = Nibble::EventBus::GetInstance();

	// Main loop
	while (m_running)
	{
		// Screen buffer update
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Verify if the main loop must be closed
		std::shared_ptr<Event> winClose = bus.DispatchEvent(Event::EventType::WindowClose);
		if (winClose != nullptr && winClose->IsHandled()) break;

		// Notify listeners on event
		bus.Process(m_LayerStack);

		// Update
		for (std::shared_ptr<Layer> l : m_LayerStack) l->OnUpdate();

		m_window->OnUpdate();
	}
}
