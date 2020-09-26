#pragma once

#include "pch.h"
#include "Core/MacroCore.h"
#include "Events/Event.h"

namespace Nibble {
	struct WindowConfiguration
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowConfiguration(
			const std::string& title = "Nible render eng",
			unsigned int width = 1280,
			unsigned int height = 720
		)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class NIBBLE_API IWindow
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		virtual ~IWindow() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual IWindow* Create(const WindowConfiguration& props = WindowConfiguration()) = 0;
	};
}
