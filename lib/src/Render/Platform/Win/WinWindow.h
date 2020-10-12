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
		};

		WindowData m_data;
		GLFWwindow* m_window;

		bool m_isPossibleCloseWindow = true;
		bool m_isClosed = false;

		virtual void Init(const WindowConfiguration& props);

		inline static auto WindowResizeCallback(
			GLFWwindow* win,
			int w,
			int h
		) -> void;
		inline static auto WindowCloseCallback(
			GLFWwindow* win
		) -> void;
	public:
		WinWindow();
		WinWindow(const WindowConfiguration& cfg);

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

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		bool IsShootdown() const override;
	};
}
