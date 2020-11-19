#pragma once

#include "Event/Event.h"

namespace Nibble {
	class NIBBLE_API MouseButtonEvent : public Event {
	public: 
		MouseButtonEvent(int button) : m_Button(button) {}

		inline int GetMouseButton() const 
		{
			return m_Button; 
		}
	protected:
		int m_Button;
		int m_CategoryFlags = EventCategory::Mouse | EventCategory::Input;
	};
}
