#pragma once

#include "IEvent.h"
namespace FluidEngine
{
	class WindowSizeChanged : public IEvent
	{
	public:
		typedef IEvent base;
		WindowSizeChanged(int width, int height) : m_Wdith(width), m_Height(height)
		{
			type = EventTypes::WindowSizeChanged;
		}
	protected:
	private:
		int m_Wdith, m_Height;

	};
}
