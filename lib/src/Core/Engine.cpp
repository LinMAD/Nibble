#include "pch.h"
#include "Engine.h"
#include "Traceability/Logger.h"
#include "glad/glad.h"

Nibble::Engine* Nibble::Engine::s_Instance = nullptr;

Nibble::Engine::Engine()
{
	NIBBLE_CORE_ASSERT(!s_Instance, "Nibble enigne instance already exists!");
	s_Instance = this;

	WinWindow window;
	m_Window = std::unique_ptr<IWindow>(window.Create());

	m_GuiLayer = std::make_shared<GuiLayer>();
	PushLayer(m_GuiLayer);
}

void Nibble::Engine::PushLayer(std::shared_ptr<ILayer> l)
{
	m_LayerStack.PushLayer(l);
}

void Nibble::Engine::PushOverlay(std::shared_ptr<ILayer> ol)
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
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Verify if the main loop must be closed
		std::shared_ptr<Event> winClose = bus.DispatchEvent(Event::EventType::WindowClose);
		if (winClose != nullptr && winClose->IsHandled()) break;

		// Notify listeners on event
		bus.Process(m_LayerStack);

		// Update
		for (std::shared_ptr<ILayer> l : m_LayerStack)
		{
			if (l == nullptr) continue;
			l->OnUpdate();
		}

		m_Window->OnUpdate();
	}
}
