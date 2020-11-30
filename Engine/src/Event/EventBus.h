#pragma once

#include "pch.h"
#include "Event/Event.h"
#include "Layer/LayerStack.h"

namespace Nibble {
	class EventBus {
	private:
		static EventBus s_Instance;
		std::vector<std::shared_ptr<Event>> m_Events;

		EventBus() {};
	public:
		EventBus(const EventBus&) = delete;

		/// <summary>
		/// Returns singleton of instance
		/// </summary>
		/// <returns></returns>
		inline static EventBus& GetInstance()
		{
			return s_Instance;
		}

		/// <summary>
		/// Get event from bus
		/// </summary>
		/// <param name="type"></param>
		/// <returns>Event or nullptr</returns>
		std::shared_ptr<Event> DispatchEvent(Event::EventType type);

		/// <summary>
		/// Simply add Event aka populate
		/// </summary>
		/// <param name="e"></param>
		void RegisterEvent(std::shared_ptr<Event> e);

		/// <summary>
		/// Handle and remove all populated events in bus
		/// </summary>
		/// <param name="ls"></param>
		void Process(LayerStack ls);
	};
}

#define EVENT_BUS_ADD_EVENT(...)::Nibble::EventBus::GetInstance().RegisterEvent(__VA_ARGS__);

