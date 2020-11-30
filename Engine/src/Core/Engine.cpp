#include "pch.h"
#include "Engine.h"
#include "DeltaTime.h"
#include "Traceability/Logger.h"

#ifdef NIBBLE_PLATFORM_WINDOWS
#include "Platform/Windows/WinWindow.h"
#endif // NIBBLE_PLATFORM_WINDOWS

namespace Nibble {
	Engine* Nibble::Engine::s_Instance = nullptr;

	Engine::Engine()
	{
		M_NIBBLE_ENG_ASSERT(!s_Instance, "Nibble enigne instance already exists!");
		s_Instance = this;

		#ifdef NIBBLE_PLATFORM_WINDOWS
		WinWindow window;
		m_Window = std::unique_ptr<Window>(window.Create());
		#endif // NIBBLE_PLATFORM_WINDOWS

		m_GuiLayer = std::make_shared<GuiLayer>();
		PushLayer(m_GuiLayer);
	}

	Engine::~Engine()
	{
	}

	void Engine::PushLayer(std::shared_ptr<Layer> l)
	{
		m_LayerStack.PushLayer(l);
	}

	void Engine::PushOverlay(std::shared_ptr<Layer> ol)
	{
		m_LayerStack.PushOverlay(ol);
	}

	void Engine::Run()
	{
		M_LOGGER_ENG_DEBUG("Executing main engine loop...");
		EventBus& bus = Nibble::EventBus::GetInstance();

		// Main loop
		while (m_Running)
		{
			float currentTime;

			#ifdef NIBBLE_PLATFORM_WINDOWS
			currentTime = (float)glfwGetTime();
			#endif // NIBBLE_PLATFORM_WINDOWS

			DeltaTime deltaTime = currentTime - m_LastFrameTimeInSeconds;
			m_LastFrameTimeInSeconds = currentTime;

			// Verify if the main loop must be closed
			std::shared_ptr<Event> winClose = bus.DispatchEvent(Event::EventType::WindowClose);
			if (winClose != nullptr && winClose->IsHandled()) break;

			// Notify listeners on event
			bus.Process(m_LayerStack);

			// Update
			for (std::shared_ptr<Layer> l : m_LayerStack)
			{
				if (l == nullptr) continue;
				l->OnUpdate(deltaTime);
			}

			m_GuiLayer->BiginFrameRender();
			for (std::shared_ptr<Layer> l : m_LayerStack)
			{
				l->OnGuiUpdate();
			}
			m_GuiLayer->EndFrameRender();

			m_Window->OnUpdate();
		}
	}
}
