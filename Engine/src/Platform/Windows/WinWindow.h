#pragma once
#include "Platform/Window.h"
#include "Graphic/OpenGL/GLContext.h"
#include <GLFW/glfw3.h>

namespace Nibble {
	/// <summary>
	/// Implementaion of Windows window
	/// </summary>
	class WinWindow : public Window {
	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
		};

		WindowData m_Data;
		GLFWwindow* m_Window;

		virtual void Init(const WindowConfiguration& props);

		inline static auto GlfwErrorCallback(int error, const char* description) -> void;

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

		inline static auto KeyButtonCallback(
			GLFWwindow* window, 
			int key, 
			int scancode, 
			int action, 
			int mods
		) -> void;

		inline static auto KeyCharacterCallback(
			GLFWwindow* window,
			unsigned int keycode
		) -> void;
	public:
		WinWindow();
		WinWindow(const WindowConfiguration& cfg);
		~WinWindow();

		virtual Window* Create(const WindowConfiguration& props = WindowConfiguration()) override;

		void OnUpdate() override;

		inline virtual void* GetNativeWindow() const { return m_Window; }

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
