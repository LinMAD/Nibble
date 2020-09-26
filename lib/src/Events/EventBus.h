#include "Events/Event.h"

namespace Nibble {
	class EventBus
	{
	private:
		std::vector<std::function<void(Event)>> m_receivers;
		std::queue<Event> m_events;
	public:
		EventBus() {};
		~EventBus() {};

		void AddReceiver(std::function<void(Event)> eventReceiver)
		{
			m_receivers.push_back(eventReceiver);
		}

		void SendEvent(Event e)
		{
			m_events.push(e);
		}

		void Notify()
		{
			while (!m_events.empty())
			{
				for (auto iter = m_receivers.begin(); iter != m_receivers.end(); iter++)
				{
					(*iter)(m_events.front());
				}

				m_events.pop();
			}
		}
	};
}