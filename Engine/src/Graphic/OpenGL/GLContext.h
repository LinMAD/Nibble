#pragma once

#include "Graphic/GraphicsContext.h"

struct GLFWwindow;

namespace Nibble {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_Window;
	};
}
