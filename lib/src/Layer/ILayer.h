#pragma once

#include "Core/MacroCore.h"
#include "Event/Event.h"

namespace Nibble {
	class NIBBLE_API ILayer
	{
	public:
		ILayer(const std::string& layerName = "Abstract render layer");
		virtual ~ILayer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName = "";
	};
}

