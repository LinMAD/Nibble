#pragma once

#include "Layer/ILayer.h"
#include "Event/Window/WindowResizeEvent.h"
#include "Event/Mouse/MouseButtonPressedEvent.h"

namespace Nibble {
	class GuiLayer : public ILayer {
	public:
		GuiLayer();
		~GuiLayer();

		void OnAttach();
		void OnDetach();

		void OnUpdate() override;
		void OnEvent(Event& e) override;
	private:
		float m_Time = 0.0f;

		void OnWindowResizeEvent(WindowResizeEvent& e);
		void OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		//bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		//bool OnMouseMovedEvent(MouseMovedEvent& e);
		//bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		//bool OnKeyPressedEvent(KeyPressedEvent& e);
		//bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		//bool OnKeyTypedEvent(KeyTypedEvent& e);
	};
}
