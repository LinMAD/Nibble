#pragma once

#include "Event/Event.h"

namespace Nibble {
	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

		virtual void SetIsHandled() override;
		virtual const char* GetName() override;
		virtual int GetCategoryFlags() override;
		virtual EventType GetEventType() override;
		virtual std::string ToString() override;

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }
	protected:
		const char* m_Name = "MouseScrolledEvent";
		int m_CategoryFlags = EventCategory::Mouse | EventCategory::Input;
		EventType m_EventType = EventType::MouseScrolled;
	private:
		float m_XOffset, m_YOffset;
	};
}
