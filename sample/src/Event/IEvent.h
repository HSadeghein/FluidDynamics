#pragma once
namespace FluidEngine
{
	class IEvent
	{
	public:
	protected:
		EventTypes type = EventTypes::None;
	private:

	};

	enum class EventTypes
	{
		None = 0,
		MouseMoved,
		LeftMouseClicked,
		RightMouseClicked,
		KeyPressed,
		KeyReleased,
		WindowSizeChanged

	};
}