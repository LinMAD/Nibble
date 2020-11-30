#pragma once

namespace Nibble {
	/// <summary>
	/// Simple Graphical API context
	/// </summary>
	class GraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
