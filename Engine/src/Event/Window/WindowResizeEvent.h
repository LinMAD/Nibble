#pragma once

#include "Event/Event.h"

namespace Nibble {
	class WindowResizeEvent : public Event {
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
		virtual std::string ToString() override;
	protected:
		const char* m_Name = "WindowResizeEvent";
		int m_CategoryFlags = EventCategory::Window;
		EventType m_EventType = EventType::WindowResize;
	private:
		unsigned int m_Width, m_Height;
	};
}
