#pragma once

#include "pch.h"
#include "Event/Event.h"
#include "EventBus.h"

namespace Nibble {
	EventBus EventBus::s_Instance;

	void EventBus::RegisterEvent(Event* e)
	{
		m_Events.push_back(e);
	}

	void EventBus::RemoveEvent(Event* e)
	{
		auto iterator = std::find(m_Events.begin(), m_Events.end(), e);

		if (iterator != m_Events.end())
			m_Events.erase(iterator);
	}

	void EventBus::HandleEvents()
	{
		for (Event* e : m_Events)
		{
			if (e->Handle())
				RemoveEvent(e);
		}
	}
}
