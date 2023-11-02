#pragma once

#include <unordered_map>
#include <list>

#include <Oasis/Events/Event.h>

namespace Oasis {

	class BaseEventHandler
	{
	private:
		virtual void Call(Event& e) = 0;
	public:
		void Exec(Event& e)
		{
			Call(e);
		}
	};

	template<typename T>
	class MethodEventHandler : public BaseEventHandler
	{
		typedef void (T::*EventFunctionPointer)(Event& e);
	private:
		T* m_Instance;

		EventFunctionPointer m_Function;
	public:
		MethodEventHandler(T* instance, EventFunctionPointer function)
			: m_Instance(instance), m_Function(function)
		{
		}
	private:
		virtual void Call(Event& e) override
		{
			(m_Instance->*m_Function)(e);
		}
	};

	class EventBus
	{
	private:
		static std::list<BaseEventHandler*> s_EventHandlers;
	public:
		static void Send(Event& e)
		{
			for (auto& handler : s_EventHandlers)
			{
				if (handler != nullptr)
				{
					if (e.Handled)
						break;
					handler->Exec(e);
				}
			}
		}

		template<typename T>
		static void Subscribe(T* instance, void (T::*function)(Event&))
		{
			s_EventHandlers.push_back(new MethodEventHandler<T>(instance, function));
		}
	};

}
