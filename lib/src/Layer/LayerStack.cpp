#include "pch.h"
#include "LayerStack.h"

namespace Nibble {
	LayerStack::LayerStack()
	{
		m_LayersInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (std::shared_ptr<Layer> l : m_Layers) l.reset();
	}

	void LayerStack::PushLayer(std::shared_ptr<Layer> l)
	{
		m_LayersInsert = m_Layers.emplace(m_LayersInsert, l);
	}

	void LayerStack::PushOverlay(std::shared_ptr<Layer> ol)
	{
		m_Layers.emplace_back(ol);
	}

	void LayerStack::PopLayer(std::shared_ptr<Layer> l)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), l);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayersInsert--;
		}
	}

	void LayerStack::PopOverlay(std::shared_ptr<Layer> ol)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), ol);
		if (it != m_Layers.end()) m_Layers.erase(it);
	}
}