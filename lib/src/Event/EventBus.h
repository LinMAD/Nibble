#pragma once

#include "pch.h"
#include "Event/Event.h"

namespace Nibble {
	class NIBBLE_API EventBus {
	private:
		static EventBus s_Instance;
		std::vector<Event*> m_Events;

		EventBus() {};
	public:
		EventBus(const EventBus&) = delete;

		static EventBus& GetInstance()
		{
			return s_Instance;
		}

		void RegisterEvent(Event* e);
		void RemoveEvent(Event* e);
		void HandleEvents();
	};
}
