#pragma once

#include "KeyEvent.h"

namespace Nibble {
	class NIBBLE_EXPORT_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		virtual void SetIsHandled() override;
		virtual const char* GetName() override;
		virtual int GetCategoryFlags() override;
		virtual EventType GetEventType() override;
		virtual std::string ToString() override;
	protected:
		EventType m_EventType = EventType::KeyReleased;
		const char* m_Name = "KeyReleasedEvent";
	};
}
