#pragma once

#include "Events/Event.h"

namespace Nibble {
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{
			m_type = EventType::WindowResize;
			m_category = EventCategory::Window;
		}

		virtual const char* GetName() const
		{
			return "WindowClose"; // EventType::WindowClose
		}

		std::string ToString() const override
		{
			return "WindowCloseEvent: Gracefully closing window..."
		}
	};
}
