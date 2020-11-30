#include "pch.h"
#include "SceneManager.h"
#include "Graphic/OpenGL/GLShader.h"

namespace Nibble {
	Renderer* SceneManager::s_RendererImpl = Renderer::GetActuallRenderer();
	std::unique_ptr<SceneManager::SceneData> SceneManager::s_SceneData = std::make_unique<SceneData>();

	void SceneManager::Begin(OrthographicCamera& camera, const glm::vec4& clearColor)
	{
		s_RendererImpl->Clear(clearColor);

		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void SceneManager::Submit(
		const std::shared_ptr<Shader>& shader, 
		const std::shared_ptr<VertexArrayBuffer>& vertexArray,
		const glm::mat4& modelMatrix
	)
	{
		shader->Lock();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", modelMatrix);

		vertexArray->Lock();
		s_RendererImpl->Draw(vertexArray);
	}

	void SceneManager::End()
	{
	}
}
