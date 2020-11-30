#pragma once

#include "pch.h"
#include "Core/MacroCore.h"
#include "Graphic/GraphicsContext.h"

namespace Nibble {
	/// <summary>
	/// Core data about applicaiton window
	/// </summary>
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

	/// <summary>
	/// Iterface for application window
	/// </summary>
	class Window
	{
	public:
		virtual void OnUpdate() = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual Window* Create(const WindowConfiguration& props = WindowConfiguration()) = 0;
	protected:
		GraphicsContext* m_GraphicsContext;
	};
}
