#pragma once

#include "Layer/ILayer.h"

namespace Nibble {
	class GuiLayer : public ILayer {
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
