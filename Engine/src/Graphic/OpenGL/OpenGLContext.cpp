#include "pch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Nibble {

	OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window(window)
	{
		M_NIBBLE_ENG_ASSERT(window, "Window is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);

		int state = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		M_NIBBLE_ENG_ASSERT(state, "Failed to initialize GLAD");

		M_LOGGER_ENG_INFO("Graphics context OpenGL");
		if (glGetString(GL_RENDERER) != nullptr)
			M_LOGGER_ENG_INFO("|_ Renderer: {0}", glGetString(GL_RENDERER));
		if (glGetString(GL_VENDOR) != nullptr)
			M_LOGGER_ENG_INFO("|_ Vendor: {0}", glGetString(GL_VENDOR));
		if (glGetString(GL_VERSION) != nullptr)
			M_LOGGER_ENG_INFO("|_ Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}
