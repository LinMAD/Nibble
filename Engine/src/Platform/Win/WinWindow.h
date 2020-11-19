#pragma once
#include "Platform/IWindow.h"
struct GLFWwindow;

namespace Nibble {
	class WinWindow : public IWindow {
	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
		};

		WindowData m_Data;
		GLFWwindow* m_Window;

		bool m_IsPossibleCloseWindow = true;

		virtual void Init(const WindowConfiguration& props);

		inline static auto WindowResizeCallback(
			GLFWwindow* win,
			int w,
			int h
		) -> void;

		inline static auto WindowCloseCallback(
			GLFWwindow* win
		) -> void;

		inline static auto MouseButtonCallback(
			GLFWwindow* window, 
			int button, 
			int action, 
			int mods
		) -> void;

		inline static auto MouseCursorPostionCallback(
			GLFWwindow* window, 
			double xPos, 
			double yPos
		) -> void;

		inline static auto MouseScrollPostionCallback(
			GLFWwindow* window,
			double xOffset,
			double yOffset
		) -> void;
	public:
		WinWindow();
		WinWindow(const WindowConfiguration& cfg);
		~WinWindow();

		virtual IWindow* Create(const WindowConfiguration& props = WindowConfiguration()) override;

		void OnUpdate() override;

		inline unsigned int GetWidth() const override
		{
			return m_Data.Width;
		}

		inline unsigned int GetHeight() const override
		{
			return m_Data.Height;
		}

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	};
}
