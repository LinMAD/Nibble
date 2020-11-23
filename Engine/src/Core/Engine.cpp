#include "pch.h"
#include "Engine.h"
#include "Traceability/Logger.h"
#include "glad/glad.h"

Nibble::Engine* Nibble::Engine::s_Instance = nullptr;

Nibble::Engine::Engine()
{
	M_NIBBLE_ENG_ASSERT(!s_Instance, "Nibble enigne instance already exists!");
	s_Instance = this;

	WinWindow window;
	m_Window = std::unique_ptr<IWindow>(window.Create());

	m_GuiLayer = std::make_shared<GuiLayer>();
	PushLayer(m_GuiLayer);

	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

	float vertices[3 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	glGenBuffers(1, &m_IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

	unsigned int indices[3] = { 0, 1, 2 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Nibble::Engine::PushLayer(std::shared_ptr<ILayer> l)
{
	m_LayerStack.PushLayer(l);
}

void Nibble::Engine::PushOverlay(std::shared_ptr<ILayer> ol)
{
	m_LayerStack.PushOverlay(ol);
}

void Nibble::Engine::Run()
{
	M_LOGGER_ENG_DEBUG("Executing main loop...");
	EventBus& bus = Nibble::EventBus::GetInstance();

	// Main loop
	while (m_Running)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

		// Verify if the main loop must be closed
		std::shared_ptr<Event> winClose = bus.DispatchEvent(Event::EventType::WindowClose);
		if (winClose != nullptr && winClose->IsHandled()) break;

		// Notify listeners on event
		bus.Process(m_LayerStack);

		// Update
		for (std::shared_ptr<ILayer> l : m_LayerStack)
		{
			if (l == nullptr) continue;
			l->OnUpdate();
		}

		m_GuiLayer->BiginFrameRender();
		for (std::shared_ptr<ILayer> l : m_LayerStack)
			l->OnGuiUpdate();
		m_GuiLayer->EndFrameRender();

		m_Window->OnUpdate();
	}
}
