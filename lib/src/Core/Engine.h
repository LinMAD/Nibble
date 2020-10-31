#pragma once

#include "Core/MacroCore.h"
#include "Render/Window/Platform/Win/WinWindow.h"

namespace Nibble {
	class NIBBLE_API Engine
	{
	private:
		std::unique_ptr<IWindow> m_window;

		bool m_running = true;
	public:
		Engine();
		virtual ~Engine();

		void Run();
	};

	Engine* InitilizeEngine();
}
