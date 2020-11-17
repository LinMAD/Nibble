#pragma once

#include "Layer/ILayer.h"

namespace Nibble {
	class GuiLayer : public ILayer {
	public:
		GuiLayer();
		~GuiLayer();

		void OnAttach();
		void OnDetach();

		void OnUpdate();
		void OnEvent(Event& e);
	private:
		float m_Time;
	};
}
