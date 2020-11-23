#pragma once

#include "Graphic/IGraphicsContext.h"

struct GLFWwindow;

namespace Nibble {
	class OpenGLContext : public IGraphicsContext {
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_Window;
	};
}
