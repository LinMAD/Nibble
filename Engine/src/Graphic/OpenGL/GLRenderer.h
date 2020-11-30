#pragma once

#include "Graphic/Renderer.h"

namespace Nibble {
	class GLRenderer : public Renderer
	{
	protected:
		virtual void DoClear(const glm::vec4& color) override;
		virtual void DoDrawIndexes(const std::shared_ptr<VertexArrayBuffer>& vertexArrayBuffer) override;
	};
}
