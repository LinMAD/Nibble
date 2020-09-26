#pragma once

#include <GLFW/glfw3.h>

#include "Render/IWindow.h"

namespace Nibble {
	class WinWindow : public IWindow {
	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFunc EventCallback;
		};

		WindowData m_data;
		GLFWwindow* m_window;

		virtual void Init(const WindowConfiguration& props);
		virtual void Shutdown();
	public:
		WinWindow();
		WinWindow(const WindowConfiguration& props);
		virtual ~WinWindow();

		virtual IWindow* Create(const WindowConfiguration& props = WindowConfiguration()) override;

		void OnUpdate() override;

		inline unsigned int GetWidth() const override
		{
			return m_data.Width;
		}

		inline unsigned int GetHeight() const override
		{
			return m_data.Height;
		}

		inline void SetEventCallback(const EventCallbackFunc& callback) override
		{
			m_data.EventCallback = callback;
		}

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	};
}
