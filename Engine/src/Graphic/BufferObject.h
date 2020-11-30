#pragma once

#include "Shader.h"

namespace Nibble {
	struct BufferElement
	{
		std::string Name;
		Shader::DataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement();

		BufferElement(
			Shader::DataType type,
			const std::string& name,
			bool normalized = false
		) :
			Name(name),
			Type(type),
			Size(Shader::DataTypeSize(type)),
			Offset(0),
			Normalized(normalized)
		{}

		/// <summary>
		/// Return component elements count by for shader data type
		/// </summary>
		/// <returns></returns>
		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case Shader::DataType::Float:   return 1;
			case Shader::DataType::Float2:  return 2;
			case Shader::DataType::Float3:  return 3;
			case Shader::DataType::Float4:  return 4;
			case Shader::DataType::Mat3:    return 3 * 3;
			case Shader::DataType::Mat4:    return 4 * 4;
			case Shader::DataType::Int:     return 1;
			case Shader::DataType::Int2:    return 2;
			case Shader::DataType::Int3:    return 3;
			case Shader::DataType::Int4:    return 4;
			case Shader::DataType::Bool:    return 1;
			}

			M_LOGGER_ENG_ERROR("Unknown ShaderDataType to return component count");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const 
		{ 
			return m_Stride; 
		}
		inline const std::vector<BufferElement>& GetElements() const 
		{ 
			return m_Elements; 
		}

		std::vector<BufferElement>::iterator begin() 
		{ 
			return m_Elements.begin(); 
		}
		std::vector<BufferElement>::iterator end() 
		{ 
			return m_Elements.end();
		}
		std::vector<BufferElement>::const_iterator begin() const 
		{ 
			return m_Elements.begin(); 
		}
		std::vector<BufferElement>::const_iterator end() const 
		{ 
			return m_Elements.end();
		}
	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;

			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	//
	// Buffer implementations
	//

	class BaseBuffer {
	public:
		virtual void Lock() const = 0;
		virtual void Unlock() const = 0;
	};

	class VertexBuffer : public BaseBuffer {
	public:
		virtual ~VertexBuffer() {};

		static VertexBuffer* SetData(float* vertices, uint32_t size);
		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
	};

	class IndexBuffer : public BaseBuffer {
	public:
		virtual ~IndexBuffer() {};

		static IndexBuffer* SetData(uint32_t* indices, uint32_t count);
		virtual uint32_t GetCount() const = 0;
	};

	class VertexArrayBuffer : public BaseBuffer {
	public:
		virtual ~VertexArrayBuffer() {};

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArrayBuffer* Create();
	};
}
