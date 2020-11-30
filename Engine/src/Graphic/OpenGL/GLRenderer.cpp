#include "pch.h"
#include "GLRenderer.h"
#include <glad/glad.h>

void Nibble::GLRenderer::DoClear(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Nibble::GLRenderer::DoDrawIndexes(const std::shared_ptr<VertexArrayBuffer>& vertexArrayBuffer)
{
	glDrawElements(GL_TRIANGLES, vertexArrayBuffer->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
