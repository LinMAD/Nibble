#pragma once

#include "Event/Event.h"

namespace Nibble {
	class NIBBLE_EXPORT_API KeyEvent : public Event {
	public:
		KeyEvent(int keycode) : m_KeyCode(keycode) {}

		inline int GetKeyCode() const 
		{ 
			return m_KeyCode; 
		}
	protected:
		int m_CategoryFlags = EventCategory::Keyboard | EventCategory::Input;
		int m_KeyCode;
	};
}
