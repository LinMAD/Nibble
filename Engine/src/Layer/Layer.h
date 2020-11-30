#pragma once

#include "Core/MacroCore.h"
#include "Core/DeltaTime.h"
#include "Event/Event.h"

namespace Nibble {
	/// <summary>
	/// Interface for layers
	/// </summary>
	class Layer
	{
	public:
		Layer(const std::string& layerName = "Abstract render layer") : m_DebugName(layerName) {};
		virtual ~Layer() {};

		/// <summary>
		/// Called when added to stack
		/// </summary>
		virtual void OnAttach() {}

		/// <summary>
		/// Called when will be removed from stack
		/// </summary>
		virtual void OnDetach() {}

		/// <summary>
		/// Called for each frame update
		/// </summary>
		virtual void OnUpdate(DeltaTime timestep) {}

		/// <summary>
		/// Same as regular update but for GUI only
		/// </summary>
		virtual void OnGuiUpdate() {}

		/// <summary>
		/// Called when event must be announced
		/// </summary>
		/// <param name="e"></param>
		virtual void OnEvent(Event& e) {}

		/// <summary>
		/// Returned given name
		/// </summary>
		/// <returns></returns>
		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName = "";
	};
}

