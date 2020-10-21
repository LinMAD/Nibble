#pragma once

#include "pch.h"
#include "Event/Event.h"

namespace Nibble {
	class NIBBLE_API WindowResizeEvent : public Event {
	private:
		unsigned int m_Width, m_Height;
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
		virtual const char* GetName() const override;
		virtual int GetCategoryFlags() const override;
		virtual EventType GetEventType() const override;
	};
}