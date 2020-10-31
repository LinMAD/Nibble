#pragma once

#include "pch.h"
#include "Event/Event.h"

namespace Nibble {
	class NIBBLE_API WindowsCloseEvent : public Event {
	public:
		// Inherited via Event
		virtual void SetIsHandled() override;
		virtual const char* GetName() override;
		virtual int GetCategoryFlags() override;
		virtual EventType GetEventType() override;
	protected:
		const char* m_name = "WindowsCloseEvent";
		int m_categoryFlags = EventCategory::Window;
		EventType m_eventType = EventType::WindowClose;
	};
}
