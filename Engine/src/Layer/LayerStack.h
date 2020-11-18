#pragma once

#include "Core/MacroCore.h"
#include "ILayer.h"

namespace Nibble {
	class NIBBLE_API LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(std::shared_ptr<ILayer> l);
		void PushOverlay(std::shared_ptr<ILayer> ol);
		void PopLayer(std::shared_ptr<ILayer> l);
		void PopOverlay(std::shared_ptr<ILayer> ol);

		std::vector<std::shared_ptr<ILayer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<std::shared_ptr<ILayer>>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<std::shared_ptr<ILayer>> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}
