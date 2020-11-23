#pragma once

#include "Core/MacroCore.h"
#include "Platform/IWindow.h"
#include "Platform/Windows/WinWindow.h"
#include "Layer/Gui/GuiLayer.h"
#include "Layer/LayerStack.h"

namespace Nibble {
	class NIBBLE_EXPORT_API Engine
	{
	public:
		Engine();
		virtual ~Engine() {};

		virtual void OnEvent(Event& e) {};
		void PushLayer(std::shared_ptr<ILayer> l);
		void PushOverlay(std::shared_ptr<ILayer> ol);

		void Run();

		inline IWindow& GetWindow() 
		{
			return *m_Window; 
		}
		inline static Engine& GetInstance() 
		{ 
			return *s_Instance;
		}
	private:
		static Engine* s_Instance;

		std::unique_ptr<IWindow> m_Window;
		LayerStack m_LayerStack;
		std::shared_ptr<GuiLayer> m_GuiLayer;

		bool m_Running = true;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	};

	Engine* InitilizeEngine();
}
