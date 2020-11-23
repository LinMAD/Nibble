#pragma once

#include "Event/Event.h"

namespace Nibble {
	class NIBBLE_EXPORT_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

		virtual void SetIsHandled() override;
		virtual const char* GetName() override;
		virtual int GetCategoryFlags() override;
		virtual EventType GetEventType() override;
		virtual std::string ToString() override;

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }
	protected:
		const char* m_Name = "MouseMovedEvent";
		int m_CategoryFlags = EventCategory::Mouse | EventCategory::Input;
		EventType m_EventType = EventType::MouseMoved;
	private:
		float m_MouseX, m_MouseY;
	};
}

