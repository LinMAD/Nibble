#pragma once

#include "Events/Event.h"

namespace Nibble {
	class WindowResizeEvent : public Event
	{
	private:
		unsigned int m_width, m_height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height)
		{
			m_type = EventType::WindowResize;
			m_category = EventCategory::Window;
		}

		unsigned int GetWidth() const
		{
			return m_width;
		}
		unsigned int GetHeight() const
		{
			return m_height;
		}

		virtual const char* GetName() const
		{
			return "WindowResize"; // EventType::WindowResize
		}

		std::string ToString() const override
		{
			std::stringstream strStream;
			strStream << "WindowResizeEvent: " << m_width << ", " << m_height;

			return strStream.str();
		}
	};
}