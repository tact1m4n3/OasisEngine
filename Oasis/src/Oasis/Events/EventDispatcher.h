#pragma once

#include <Oasis/Events/Event.h>

namespace Oasis {

	class EventDispatcher
	{
	private:
		Event& m_Event;
	public:
		EventDispatcher(Event& e)
			: m_Event(e)
		{
		}

		template<typename T, typename EventType>
		void Subscribe(T* instance, void (T::*function)(EventType&))
		{
			if (m_Event.GetEventType() == EventType::GetStaticType())
			{
				(instance->*function)(static_cast<EventType&>(m_Event));
			}
		}
	};

}