#include "pch.h"
#include "BufferObject.h"
#include "Renderer.h"
#include "OpenGL/GLBufferObject.h"

Nibble::BufferElement::BufferElement()
{

}

Nibble::VertexBuffer* Nibble::VertexBuffer::SetData(float* vertices, uint32_t size)
{
	switch (Renderer::GetType())
	{
	case Renderer::Type::OpenGL:
		return new GLVertexBuffer(vertices, size);
	default:
		M_NIBBLE_ENG_ASSERT(false, "Not set or not found supported renderer!");
		return nullptr;
	}
}

Nibble::IndexBuffer* Nibble::IndexBuffer::SetData(uint32_t* indices, uint32_t count)
{
	switch (Renderer::GetType())
	{
	case Renderer::Type::OpenGL:
		return new GLIndexBuffer(indices, count);
	default:
		M_NIBBLE_ENG_ASSERT(false, "Not set or not found supported renderer!");
		return nullptr;
	}
}

Nibble::VertexArrayBuffer* Nibble::VertexArrayBuffer::Create()
{
	switch (Renderer::GetType())
	{
	case Renderer::Type::OpenGL:
		return new GLVertexArrayBuffer();
	default:
		M_NIBBLE_ENG_ASSERT(false, "Not set or not found supported renderer!");
		return nullptr;
	}
}
