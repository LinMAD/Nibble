#pragma once

#include "Graphic/BufferObject.h"

namespace Nibble {
	class GLVertexBuffer : public VertexBuffer {
	public:
		GLVertexBuffer(float* vertices, uint32_t size);
		~GLVertexBuffer();

		virtual void Lock() const override;
		virtual void Unlock() const override;
		virtual const BufferLayout& GetLayout() const override 
		{ 
			return m_Layout; 
		}
		virtual void SetLayout(const BufferLayout& layout) override 
		{ 
			m_Layout = layout; 
		}
	private:
		uint32_t m_RendererId;
		BufferLayout m_Layout;
	};

	class GLIndexBuffer : public IndexBuffer {
	public:
		GLIndexBuffer(uint32_t* indices, uint32_t count);
		~GLIndexBuffer();

		virtual void Lock() const override;
		virtual void Unlock() const override;

		virtual uint32_t GetCount() const override
		{
			return m_Count;
		}
	private:
		uint32_t m_RendererId;
		uint32_t m_Count;
	};

	class GLVertexArrayBuffer : public VertexArrayBuffer {
	public:
		GLVertexArrayBuffer();
		virtual ~GLVertexArrayBuffer();

		virtual void Lock() const override;
		virtual void Unlock() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const
		{
			return m_VertexBuffers;
		}
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const 
		{
			return m_IndexBuffer;
		}
	private:
		uint32_t m_RendererId;
		uint32_t m_VertexBufferIndex = 0;

		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;

		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}
