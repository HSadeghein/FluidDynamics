#pragma once
#include <sstream>
#include "IEvent.h"
#include "Event/KeyCodes.h"
namespace FluidEngine
{
	class WindowSizeChangedEvent : public IEvent
	{
	public:
		typedef IEvent base;
		WindowSizeChangedEvent(int width, int height) : m_Wdith(width), m_Height(height)
		{
			type = EventTypes::WindowSizeChanged;
		}

		EventTypes GetEventType() const override
		{
			return type;
		}

		EVENT_CLASS_TYPE(WindowSizeChanged)


			int GetWdith() const
		{
			return m_Wdith;
		}

		int GetHeight() const
		{
			return m_Height;
		}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowSizeChanged Event: " << m_Wdith << " ," << m_Height << "\n";
			return ss.str();
		}

	protected:
	private:
		int m_Wdith, m_Height;

	};

	class WindowClosedEvent : public IEvent
	{
	public:
		WindowClosedEvent()
		{
			type = EventTypes::WindowClosed;
		}
		EventTypes GetEventType() const override
		{
			return type;
		}

		EVENT_CLASS_TYPE(WindowClosed)

			std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowClosed Event: " << "\n";
			return ss.str();

		}

	};


	class KeyEvent : public IEvent
	{
	public:



		KeyCodes GetKeyCode() { return m_KeyCode; }

	protected:
		KeyEvent(KeyCodes keyCode) : m_KeyCode(keyCode)
		{

		}
		KeyCodes m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:

		KeyPressedEvent(KeyCodes keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount)
		{
			type = EventTypes::KeyPressed;
		}

		int GetRepeatCount() { return m_RepeatCount; }


		EventTypes GetEventType() const override
		{
			return type;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressed Event : " << m_KeyCode << " Repeated : " << m_RepeatCount << "\n";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount = 0;

	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:

		KeyReleasedEvent(KeyCodes keyCode) : KeyEvent(keyCode)
		{
			type = EventTypes::KeyReleased;
		}


		EventTypes GetEventType() const override
		{
			return type;
		}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleased Event :" << m_KeyCode << "\n";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)


	};

	class KeyRepeatedEvent : public KeyEvent
	{
	public:
		KeyRepeatedEvent(KeyCodes keyCode) : KeyEvent(keyCode)
		{
			type = EventTypes::KeyRepeated;
		}

		EventTypes GetEventType() const override
		{
			return type;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Repeated Event :" << m_KeyCode << "\n";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyRepeated)
	};

	class EventTick : public IEvent
	{
	public:
		EventTick()
		{

		}
	};

	class RightMouseButtonPressed : public IEvent
	{
	public:
		RightMouseButtonPressed()
		{
			type = EventTypes::RightMouseClicked;
		}

		EventTypes GetEventType() const override
		{
			return type;
		}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Right Mouse Pressed" << '\n';
			return ss.str();
		}

		EVENT_CLASS_TYPE(RightMouseClicked)
	};

	class LeftMouseButtonPressed : public IEvent
	{
	public:
		LeftMouseButtonPressed()
		{
			type = EventTypes::LeftMouseClicked;
		}

		EventTypes GetEventType() const override
		{
			return type;
		}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Left Mouse Pressed" << '\n';
			return ss.str();
		}

		EVENT_CLASS_TYPE(LeftMouseClicked)
	};
	class RightMouseButtonReleased : public IEvent
	{
	public:
		RightMouseButtonReleased()
		{
			type = EventTypes::RightMouseReleased;
		}

		EventTypes GetEventType() const override
		{
			return type;
		}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Right mouse released" << '\n';
			return ss.str();
		}

		EVENT_CLASS_TYPE(RightMouseReleased)
	};
	class LeftMouseButtonReleased : public IEvent
	{
	public:
		LeftMouseButtonReleased()
		{
			type = EventTypes::LeftMouseReleased;
		}

		EventTypes GetEventType() const override
		{
			return type;
		}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Left mouse released" << '\n';
			return ss.str();
		}

		EVENT_CLASS_TYPE(LeftMouseReleased)
	};

	class MouseMoved : public IEvent
	{
	public:
		MouseMoved(int xPos, int yPos) : m_XPos(xPos), m_YPos(yPos)
		{
			type = EventTypes::MouseMoved;
		}
		EventTypes GetEventType() const override
		{
			return type;
		}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Moved --> X:" << m_XPos << "\t" << "Y:" << m_YPos << "\n";
			return ss.str();
		}
		int GetX() { return m_XPos; }
		int GetY() { return m_YPos; }

		EVENT_CLASS_TYPE(MouseMoved)

	private:
		int m_XPos;
		int m_YPos;
	};
}
