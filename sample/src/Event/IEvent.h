#pragma once

#include <string>
namespace FluidEngine
{
	enum class EventTypes
	{
		None = 0,
		MouseMoved,
		LeftMouseClicked,
		RightMouseClicked,
		LeftMouseReleased,
		RightMouseReleased,
		KeyPressed,
		KeyReleased,
		KeyRepeated,
		WindowSizeChanged,
		WindowClosed

	};

#define EVENT_CLASS_TYPE(type) static EventTypes GetStaticType() {return EventTypes::type;}
	class IEvent
	{
	public:
		virtual ~IEvent() = default;
		EventTypes type = EventTypes::None;

		virtual EventTypes GetEventType() const = 0;
		virtual std::string ToString() const = 0;

		bool Hanlded = false;
	protected:
	private:
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(IEvent& e) : m_Event(e)
		{

		}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Hanlded = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		IEvent& m_Event;
	};

}