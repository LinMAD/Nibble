#include "pch.h"
#include "GLBufferObject.h"
#include "GLShader.h"
#include <glad/glad.h>

namespace Nibble {

	// GLVertexBuffer
	//
	GLVertexBuffer::GLVertexBuffer(float* vertices, uint32_t size)
	{
		glGenVertexArrays(1, &m_RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	GLVertexBuffer::~GLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererId);
	}

	void GLVertexBuffer::Lock() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	}

	void GLVertexBuffer::Unlock() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	// GLIndexBuffer
    //
	GLIndexBuffer::GLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
	{
		glGenVertexArrays(1, &m_RendererId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererId);
	}

	void GLIndexBuffer::Lock() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	}

	void GLIndexBuffer::Unlock() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	// GLVertexArrayBuffer
	//
	GLVertexArrayBuffer::GLVertexArrayBuffer()
	{
		glCreateVertexArrays(1, &m_RendererId);
	}

	GLVertexArrayBuffer::~GLVertexArrayBuffer()
	{
		glDeleteVertexArrays(1, &m_RendererId);
	}

	void GLVertexArrayBuffer::Lock() const
	{
		glBindVertexArray(m_RendererId);
	}

	void GLVertexArrayBuffer::Unlock() const
	{
		glBindVertexArray(0);
	}

	void GLVertexArrayBuffer::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		M_NIBBLE_ENG_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererId);

		vertexBuffer->Lock();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);

			glVertexAttribPointer(
				m_VertexBufferIndex,
				element.GetComponentCount(),
				GLShader::ToNativeShaderType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset
			);

			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void GLVertexArrayBuffer::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererId);

		indexBuffer->Lock();

		m_IndexBuffer = indexBuffer;
	}

}
