#pragma once

#include "Graphic/Renderer.h"
#include "Graphic/Shader.h"
#include "Graphic/BufferObject.h"
#include "Camera/OrthographicCamera.h"

namespace Nibble {
	class SceneManager
	{
	public:
		/// <summary>
		/// Prepare scene
		/// </summary>
		/// <param name="camera"></param>
		/// <param name="clearColor"></param>
		static void Begin(OrthographicCamera& camera, const glm::vec4& clearColor);

		/// <summary>
		/// Submit to scene, must be used between begin and end of scene
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="vertexArrayBuffer"></param>
		/// <param name="modelMatrix">Model transform</param>
		static void Submit(
			const std::shared_ptr<Shader>& shader,
			const std::shared_ptr<VertexArrayBuffer>& vertexArray,
			const glm::mat4& modelMatrix = glm::mat4(1.0f)
		);

		/// <summary>
		/// Close scene and render it
		/// </summary>
		static void End();
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static std::unique_ptr<SceneData> s_SceneData;
		static Renderer* s_RendererImpl;
	};
}
