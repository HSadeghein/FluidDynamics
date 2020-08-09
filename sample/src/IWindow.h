#pragma once
#include <functional>
#include "Event/IEvent.h"
#include "Event/Event.h"
namespace FluidEngine
{

	enum class WindowMode
	{
		FullScreen,
		BorderlessWindow,
		Windowed
	};
	struct WindowProps
	{
		int Width, Height;
		const char* Title;
		WindowMode Mode;

		WindowProps(int width, int height, const char* title, WindowMode mode = WindowMode::Windowed) : Width(width), Height(height), Title(title), Mode(mode)
		{

		}

	};
	class IWindow
	{
	public:
		using EventCallbackFn = std::function<void(IEvent&)>;

		virtual ~IWindow() = default;

		virtual void SetWidth(int width) = 0;
		virtual void SetHeight(int height) = 0;
		virtual int GetHeight() const = 0;
		virtual int GetWidth() const = 0;
		virtual void SetWindowSize(int width, int height) = 0;
		virtual void OnUpdate() = 0;
		//virtual void OnEvent(IEvent& e) = 0;
		//virtual bool OnWindowSizeChanged(WindowSizeChangedEvent& e) = 0;
		//virtual bool OnWindowClose(WindowClosedEvent& e) = 0;
		//virtual bool OnKeyPressed(KeyPressedEvent& e) = 0;
		//virtual bool OnKeyReleased(KeyReleasedEvent& e) = 0;
		//virtual bool OnLeftMouseButtonPressed(LeftMouseButtonPressed& e) = 0;
		//virtual bool OnRightMouseButtonPressed(RightMouseButtonPressed& e) = 0;
		//virtual bool OnMouseMoved(MouseMoved& e) = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;


	};
}
