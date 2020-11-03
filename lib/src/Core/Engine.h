#pragma once

#include "Core/MacroCore.h"
#include "Render/Window/Platform/Win/WinWindow.h"
#include "Layer/LayerStack.h"

namespace Nibble {
	class NIBBLE_API Engine
	{
	private:
		std::unique_ptr<IWindow> m_window;
		LayerStack m_LayerStack;

		bool m_running = true;
	public:
		Engine();
		virtual ~Engine() {};

		virtual void OnEvent(Event& e) {};
		void PushLayer(std::shared_ptr<Layer> l);
		void PushOverlay(std::shared_ptr<Layer> ol);

		void Run();
	};

	Engine* InitilizeEngine();
}
