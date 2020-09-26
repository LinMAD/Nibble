#include "Events/EventBus.h"

namespace Nibble {
	class AbstractEventHandler
	{
	protected:
		EventBus* m_eventBus;

		std::function<void(Event)> GetNotifyFunc()
		{
			auto eventListener = [=](Event e) -> void
			{
				this->OnNotify(e);
			};

			return eventListener;
		}

		void Send(Event e)
		{
			m_eventBus->SendEvent(e);
		}

		/// <summary>
		/// Handle event on notify
		/// </summary>
		/// <param name="e"></param>
		virtual void OnNotify(Event e) {};
	public:
		AbstractEventHandler(EventBus* e)
		{
			this->m_eventBus = e;
			this->m_eventBus->AddReceiver(this->GetNotifyFunc());
		}

		/// <summary>
		/// Perform update routines for event
		/// </summary>
		virtual void update() {};
	};
}
