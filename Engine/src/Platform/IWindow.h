#pragma once

#include "pch.h"
#include "Core/MacroCore.h"

namespace Nibble {
	struct WindowConfiguration
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowConfiguration(
			const std::string& title = "Nibble render engine",
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
		virtual void OnUpdate() = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual IWindow* Create(const WindowConfiguration& props = WindowConfiguration()) = 0;
	};
}
