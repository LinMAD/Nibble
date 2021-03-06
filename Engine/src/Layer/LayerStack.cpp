#include "pch.h"
#include "LayerStack.h"

namespace Nibble {
	LayerStack::~LayerStack()
	{
		for (std::shared_ptr<Layer> l : m_Layers) l.reset();
	}

	void LayerStack::PushLayer(std::shared_ptr<Layer> l)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, l);
		m_LayerInsertIndex++;
		l->OnAttach();
	}

	void LayerStack::PushOverlay(std::shared_ptr<Layer> ol)
	{
		m_Layers.insert(m_Layers.begin(), ol);
		ol->OnAttach();
	}

	void LayerStack::PopLayer(std::shared_ptr<Layer> l)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, l);
		if (it != m_Layers.begin() + m_LayerInsertIndex)
		{
			l->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(std::shared_ptr<Layer> ol)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), ol);
		if (it != m_Layers.end())
		{
			ol->OnDetach();
			m_Layers.erase(it);
		}
	}
}
