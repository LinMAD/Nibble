#pragma once

#include "Core/MacroCore.h"
#include "Render/Window/IWindow.h"
#include "Render/Window/Platform/Win/WinWindow.h"
#include "Render/Gui/GuiLayer.h"
#include "Layer/LayerStack.h"

namespace Nibble {
	class NIBBLE_API Engine
	{
	public:
		Engine();
		virtual ~Engine() {};

		virtual void OnEvent(Event& e) {};
		void PushLayer(std::shared_ptr<ILayer> l);
		void PushOverlay(std::shared_ptr<ILayer> ol);

		void Run();

		inline IWindow& GetWindow() { return *m_Window; }
		inline static Engine& GetInstance() { return *s_Instance; }
	private:
		static Engine* s_Instance;

		std::unique_ptr<IWindow> m_Window;
		LayerStack m_LayerStack;
		std::shared_ptr<GuiLayer> m_GuiLayer;

		bool m_running = true;
	};

	Engine* InitilizeEngine();
}
