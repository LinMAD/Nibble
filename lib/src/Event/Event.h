#pragma once

#include "Core/MacroCore.h"

namespace Nibble {
	class NIBBLE_API Event {
	public:
		enum EventType
		{
			None = 0,
			WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
			WindowTick, WindowUpdate, WindowRender,
			KeyPressed, KeyReleased, KeyTyped,
			MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
		};

		enum EventCategory
		{
			Window = 1 << 0,
			Input = 1 << 1,
			Keyboard = 1 << 2,
			Mouse = 1 << 3,
			MouseButton = 1 << 4,
		};

		virtual void SetIsHandled() = 0;
		inline bool IsHandled()
		{
			return m_IsHandled;
		}

		virtual const char* GetName() = 0;
		virtual int GetCategoryFlags() = 0;
		virtual EventType GetEventType() = 0;

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
		inline bool IsType(EventType type)
		{
			return GetEventType() == type;
		}
	protected:
		bool m_IsHandled;
		const char* m_Name;
		int m_CategoryFlags;
		EventType m_EventType;
	};
}
