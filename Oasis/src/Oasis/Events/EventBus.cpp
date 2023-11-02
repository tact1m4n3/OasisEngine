#include <Oasis/Events/EventBus.h>

namespace Oasis {

	std::list<BaseEventHandler*> EventBus::s_EventHandlers;

}