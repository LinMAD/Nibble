#pragma once

#include "MouseButtonEvent.h"

namespace Nibble {
	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		virtual void SetIsHandled() override;
		virtual const char* GetName() override;
		virtual int GetCategoryFlags() override;
		virtual EventType GetEventType() override;
		virtual std::string ToString() override;
	protected:
		EventType m_EventType = EventType::MouseButtonReleased;
		const char* m_Name = "MouseButtonReleasedEvent";
	};
}
