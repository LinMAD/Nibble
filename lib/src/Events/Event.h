#pragma once

#include <string>
#include <sstream>
#include <functional>

namespace Nibble {
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
		Window = BIT_SHIFT(0),
		Input = BIT_SHIFT(1),
		Keyboard = BIT_SHIFT(2),
		Mouse = BIT_SHIFT(3),
		MouseButton = BIT_SHIFT(4)
	};

	class Event
	{
	protected:
		EventType m_type;
		EventCategory m_category;
	public:
		virtual ~Event() = default;

		bool Handled = false;

		virtual const char* GetName() const
		{
			return "";
		}

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		virtual EventType GetType()
		{
			return m_type;
		};

		virtual EventCategory GetCategoryFlags()
		{
			return m_category;
		}

		virtual std::string ToString() const
		{
			return GetName();
		}
	};
};
