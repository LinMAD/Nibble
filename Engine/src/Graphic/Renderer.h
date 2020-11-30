#pragma once

#include <glm/glm.hpp>
#include "BufferObject.h"
#include "Shader.h"

namespace Nibble {
	/// <summary>
	/// Abstract graphics renderer
	/// Delegates graphical operations 
	/// to concrete implementations of Graphical API's (s_RendererImpl)
	/// </summary>
	class Renderer 
	{
	public:
		/// <summary>
		/// Graphical API's
		/// </summary>
		enum class Type
		{
			None = 0,
			OpenGL = 1
		};

		/// <summary>
		/// Clear frame
		/// </summary>
		/// <param name="color"></param>
		inline static void Clear(const glm::vec4& color)
		{
			s_RendererImpl->DoClear(color);
		}

		/// <summary>
		/// Draw given indexes in the scene
		/// </summary>
		/// <param name="vertexArrayBuffer"></param>
		inline static void Draw(const std::shared_ptr<VertexArrayBuffer>& vertexArrayBuffer)
		{
			s_RendererImpl->DoDrawIndexes(vertexArrayBuffer);
		}

		inline static Type GetType()
		{ 
			return s_RendererType;  
		}
		inline static Renderer* GetActuallRenderer()
		{
			return s_RendererImpl.get();
		}
	protected:
		/// <summary>
		/// Must be implemented inside the inherited class
		/// </summary>
		/// <param name="color"></param>
		virtual void DoClear(const glm::vec4& color) = 0;

		/// <summary>
		/// Must be implemented inside the inherited class
		/// </summary>
		/// <param name="color"></param>
		virtual void DoDrawIndexes(const std::shared_ptr<VertexArrayBuffer>& vertexArrayBuffer) = 0;
	private:
		static Type s_RendererType;
		static std::unique_ptr<Renderer> s_RendererImpl;
	};
}
