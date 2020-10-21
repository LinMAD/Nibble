#pragma once

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
		Window = 1 << 0,
		Input = 1 << 1,
		Keyboard = 1 << 2,
		Mouse = 1 << 3,
		MouseButton = 1 << 4,
	};

	class Event {
	public:
		virtual bool Handle() = 0;
	};
}
