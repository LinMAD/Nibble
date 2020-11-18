#pragma once

#include "Event/Event.h"

namespace Nibble {
	class NIBBLE_API WindowsCloseEvent : public Event {
	public:
		// Inherited via Event
		virtual void SetIsHandled() override;
		virtual const char* GetName() override;
		virtual int GetCategoryFlags() override;
		virtual EventType GetEventType() override;
		virtual std::string ToString() override;
	protected:
		const char* m_Name = "WindowsCloseEvent";
		int m_CategoryFlags = EventCategory::Window;
		EventType m_EventType = EventType::WindowClose;
	};
}
