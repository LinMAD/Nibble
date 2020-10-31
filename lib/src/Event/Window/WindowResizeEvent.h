#pragma once

#include "pch.h"
#include "Event/Event.h"

namespace Nibble {
	class NIBBLE_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(
			unsigned int width,
			unsigned int height
		) : m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const
		{
			return m_Width;
		}
		inline unsigned int GetHeight() const
		{
			return m_Height;
		}

		// Inherited via Event
		virtual void SetIsHandled() override;
		virtual const char* GetName() override;
		virtual int GetCategoryFlags() override;
		virtual EventType GetEventType() override;
	protected:
		const char* m_name = "WindowResizeEvent";
		int m_categoryFlags = EventCategory::Window;
		EventType m_eventType = EventType::WindowResize;
	private:
		unsigned int m_Width, m_Height;
	};
}