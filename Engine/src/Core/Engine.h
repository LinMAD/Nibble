#pragma once

#include "MacroCore.h"
#include "Platform/Window.h"
#include "Layer/Gui/GuiLayer.h"
#include "Layer/LayerStack.h"

namespace Nibble {
	/// <summary>
	/// Core engine class with main loop
	/// </summary>
	class Engine
	{
	public:
		Engine();
		~Engine();

		/// <summary>
		/// Any layer grahical or data
		/// Will be handled in order
		/// </summary>
		/// <param name="l">Layer</param>
		void PushLayer(std::shared_ptr<Layer> l);

		/// <summary>
		/// Same as in PushLayer 
		/// But will be called in the end
		/// Like on top of layers
		/// </summary>
		/// <param name="ol"></param>
		void PushOverlay(std::shared_ptr<Layer> ol);

		/// <summary>
		/// Execute main loop
		/// </summary>
		void Run();

		/// <summary>
		/// Appliaction window
		/// </summary>
		/// <returns></returns>
		inline Window& GetWindow() 
		{
			return *m_Window; 
		}

		/// <summary>
		/// Engine singleton instance
		/// </summary>
		/// <returns></returns>
		inline static Engine& GetInstance() 
		{ 
			return *s_Instance;
		}
	private:
		static Engine* s_Instance;

		std::unique_ptr<Window> m_Window;
		std::shared_ptr<GuiLayer> m_GuiLayer;

		LayerStack m_LayerStack;

		bool m_Running = true;

		float m_LastFrameTimeInSeconds = 0.0f;
	};

	/// <summary>
	/// Must be implemented in client application
	/// Instead of main()
	/// 
	/// <example>
	/// class ClientApplication : public Nibble::Engine 
	/// {
	/// public:
	/// ClientApplication(){};
	/// }
	/// Nibble::Engine* Nibble::InitilizeEngine()
	/// {
	///		return new Demo::ClientApplication();
	/// }
	///
	/// </example>
	/// </summary>
	/// <returns></returns>
	Engine* InitilizeEngine();
}
