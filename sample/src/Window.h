#pragma once

#include <GLFW/glfw3.h>
#include <memory>
#include "Log.h"
#include <functional>
#include "IWindow.h"

namespace FluidEngine
{

	struct DestroyglfwWin
	{

		void operator()(GLFWwindow* ptr)
		{
			Log::GetCoreLogger()->info("deleted");
			glfwDestroyWindow(ptr);
		}

	};
	class Application;
	class Window : public IWindow
	{

		friend class FluidEngine::Application;
	public:
		Window(const WindowProps& props);
		~Window();
		void SetWidth(int width) override;
		void SetHeight(int height) override;
		int GetHeight() const override;
		int GetWidth() const override;
		void SetWindowSize(int width, int height) override;
		void OnUpdate() override;
		GLFWwindow* GetWindow();

		void RegisterApplication(std::shared_ptr<Application> application);

		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallBack = callback; };


		void OnEvent(IEvent& e) override;


		bool OnWindowSizeChanged(WindowSizeChangedEvent& e) override;

		bool OnWindowClose(WindowClosedEvent& e) override;

		bool OnKeyPressed(KeyPressedEvent& e) override;

		bool OnKeyReleased(KeyReleasedEvent& e) override;

		bool OnRightMouseButtonPressed(RightMouseButtonPressed& e) override;

		bool OnLeftMouseButtonPressed(LeftMouseButtonPressed& e) override;

		bool OnMouseMoved(MouseMoved& e) override;

	protected:
		void Terminate();



	private:
		void Init(const WindowProps& props);


		GLFWwindow* m_Window;

		std::weak_ptr<Application> m_Application;


		struct WindowData
		{
			int Width, Height;
			const char* Ttile;
			bool VSync;
			WindowMode WindowMode;
			EventCallbackFn EventCallBack;

		};
		WindowData m_Data;

	};

}