#pragma once

#include "pch.h"
#include "Event/Event.h"
#include "EventBus.h"

namespace Nibble {
	EventBus EventBus::s_Instance;

	std::shared_ptr<Event> EventBus::DispatchEvent(Event::EventType type)
	{
		std::shared_ptr<Event> neededEvent = nullptr;

		if (m_Events.size() == 0)
			return neededEvent;

		for (std::shared_ptr<Event> e : m_Events)
		{
			if (e != nullptr && e->IsType(type))
			{
				neededEvent = e;
				break;
			}
		}

		return neededEvent;
	}

	void EventBus::RegisterEvent(std::shared_ptr<Event> e)
	{
		m_Events.push_back(e);
	}

	/// <summary>
	/// Notify layers with events
	/// </summary>
	/// <param name="ls">LayerStack</param>
	void EventBus::Process(LayerStack ls)
	{
		if (m_Events.size() == 0) return;

		for (auto eventIter = m_Events.begin(); eventIter != m_Events.end();)
		{
			std::shared_ptr<Event> eventInQ = *eventIter;
			if (eventInQ == nullptr) continue;

			for (std::shared_ptr<Layer> l : ls) 
				l->OnEvent(*eventInQ);

			eventIter = m_Events.erase(eventIter);
		}
	}
}
