#pragma once

#include "KeyEvent.h"

namespace Nibble {
	class NIBBLE_API KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

		virtual void SetIsHandled() override;
		virtual const char* GetName() override;
		virtual int GetCategoryFlags() override;
		virtual EventType GetEventType() override;
		virtual std::string ToString() override;
	protected:
		EventType m_EventType = EventType::KeyTyped;
		const char* m_Name = "KeyTypedEvent";
	};
}

