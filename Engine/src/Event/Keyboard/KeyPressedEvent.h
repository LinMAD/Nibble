#pragma once

#include "KeyEvent.h"

namespace Nibble {
	class NIBBLE_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		virtual void SetIsHandled() override;
		virtual const char* GetName() override;
		virtual int GetCategoryFlags() override;
		virtual EventType GetEventType() override;
		virtual std::string ToString() override;
	protected:
		EventType m_EventType = EventType::KeyPressed;
		const char* m_Name = "KeyPressedEvent";
	private:
		int m_RepeatCount;
	};
}

