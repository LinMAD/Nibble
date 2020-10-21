#pragma once

namespace Nibble {
	class NIBBLE_API Event {
	protected:
		bool m_IsHandled = false;
	public:
		enum class EventType
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

		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual EventType GetEventType() const = 0;

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};
}
