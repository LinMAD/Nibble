#pragma once

#include "Layer/ILayer.h"
#include "Event/Window/WindowResizeEvent.h"
#include "Event/Mouse/MouseButtonPressedEvent.h"
#include "Event/Mouse/MouseButtonReleasedEvent.h"
#include "Event/Mouse/MouseMovedEvent.h"
#include "Event/Mouse/MouseScrolledEvent.h"
#include "Event/Keyboard/KeyPressedEvent.h"
#include "Event/Keyboard/KeyReleasedEvent.h"
#include "Event/Keyboard/KeyTypedEvent.h"

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
		void OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		void OnMouseMovedEvent(MouseMovedEvent& e);
		void OnMouseScrolledEvent(MouseScrolledEvent& e);
		void OnKeyPressedEvent(KeyPressedEvent& e);
		void OnKeyReleasedEvent(KeyReleasedEvent& e);
		void OnKeyTypedEvent(KeyTypedEvent& e);
	};
}
