#pragma once

#include "Layer/Layer.h"

namespace Nibble {
	class GuiLayer : public Layer {
	public:
		GuiLayer();
		~GuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnGuiUpdate() override;

		void BiginFrameRender();
		void EndFrameRender();
	};
}
