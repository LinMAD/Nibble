#pragma once

#include <Nibble.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Nibble;

namespace Playground {
	class TriangleLayer : public Layer
	{
	public:
		TriangleLayer() : Layer("Triangle Layer"), m_CameraController(1280.0f / 720.0f)
		{
			// Create triangle
			m_VertexArrayBuffer.reset(VertexArrayBuffer::Create());
			float verticesTriangle[3 * 3] = {
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f, 
				 0.0f,  0.5f, 0.0f,
			};

			m_VertexBuffer.reset(VertexBuffer::SetData(verticesTriangle, sizeof(verticesTriangle)));
			m_VertexBuffer->SetLayout({
				{ Shader::DataType::Float3, "a_Position"},
			});
			m_VertexArrayBuffer->AddVertexBuffer(m_VertexBuffer);

			// Set triangle indices
			uint32_t indicesTriangle[3] = { 0, 1, 2 };
			m_IndexBuffer.reset(IndexBuffer::SetData(indicesTriangle, sizeof(indicesTriangle) / sizeof(uint32_t)));
			m_VertexArrayBuffer->SetIndexBuffer(m_IndexBuffer);

			m_ShaderContainer.Load("assets/shaders/Triangle.vert.glsl", "assets/shaders/Triangle.frag.glsl");
		}

		void OnUpdate(DeltaTime delta) override
		{
			SceneManager::Begin(m_CameraController.GetCamera(), { 0.2f, 0.3f, 0.3f, 1.0f });

			auto triangle = m_ShaderContainer.Get("Triangle");
			triangle->Lock();
			triangle->SetFloat3("u_Color", m_Color);

			SceneManager::Submit(triangle, m_VertexArrayBuffer);

			SceneManager::End();
		}

		void OnGuiUpdate() override
		{
			ImGui::Begin("Color configuration");

			ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGuiStyle& style = ImGui::GetStyle();
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;

			ImGui::End();
		}
	private:
		Nibble::ShaderContainer m_ShaderContainer;

		std::shared_ptr<VertexArrayBuffer> m_VertexArrayBuffer;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		glm::vec3 m_Color = { 0.5f, 0.5f, 0.5f };

		OrthographicCameraController m_CameraController;
	};
}
