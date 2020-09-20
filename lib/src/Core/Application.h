#pragma once

#include "MacroCore.h"

namespace Nibble {
	class NIBBLE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplicaiton();
}
