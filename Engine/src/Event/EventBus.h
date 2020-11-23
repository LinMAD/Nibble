#pragma once

#include "pch.h"
#include "Event/Event.h"
#include "Layer/LayerStack.h"

namespace Nibble {
	class NIBBLE_EXPORT_API EventBus {
	private:
		static EventBus s_Instance;
		std::vector<std::shared_ptr<Event>> m_Events;

		EventBus() {};
	public:
		EventBus(const EventBus&) = delete;

		inline static EventBus& GetInstance()
		{
			return s_Instance;
		}

		std::shared_ptr<Event> DispatchEvent(Event::EventType type);
		void RegisterEvent(std::shared_ptr<Event> e);
		void Process(LayerStack ls);
	};
}

#define EVENT_BUS_ADD_EVENT(...)::Nibble::EventBus::GetInstance().RegisterEvent(__VA_ARGS__);

