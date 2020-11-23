#pragma once

#include "MouseButtonEvent.h"

namespace Nibble {
	class NIBBLE_EXPORT_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		virtual void SetIsHandled() override;
		virtual const char* GetName() override;
		virtual int GetCategoryFlags() override;
		virtual EventType GetEventType() override;
		virtual std::string ToString() override;
	protected:
		EventType m_EventType = EventType::MouseButtonPressed;
		const char* m_Name = "MouseButtonPressedEvent";
	};
}

