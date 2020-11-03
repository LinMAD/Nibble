#pragma once

#include "Core/MacroCore.h"
#include "Layer/Layer.h"

namespace Nibble {
	class NIBBLE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(std::shared_ptr<Layer> l);
		void PushOverlay(std::shared_ptr<Layer> ol);
		void PopLayer(std::shared_ptr<Layer> l);
		void PopOverlay(std::shared_ptr<Layer> ol);

		std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<std::shared_ptr<Layer>>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
		std::vector<std::shared_ptr<Layer>>::iterator m_LayersInsert;
	};
}
