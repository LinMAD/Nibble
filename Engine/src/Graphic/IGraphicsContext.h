#pragma once

namespace Nibble {
	class IGraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
