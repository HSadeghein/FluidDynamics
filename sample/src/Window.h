#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include "Log.h"
namespace FluidEngine
{
	enum class WindowMode
	{
		FullScreen,
		BorderlessWindow,
		Windowed
	};

	struct DestroyglfwWin {

		void operator()(GLFWwindow* ptr) {
			Log::GetCoreLogger()->info("deleted");
			glfwDestroyWindow(ptr);
		}

	};
	class Application;
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	class Window {

		friend class FluidEngine::Application;
	public:
		Window(int width, int height, WindowMode windowMode = WindowMode::Windowed);
		~Window();
		void SetWidth(int width);
		void SetHeight(int height);
		int GetHeight();
		int GetWidth();
		void SetWindowSize(int width, int height);
		GLFWwindow* GetWindow();
	protected:
		void Terminate();
	private:
		int m_Width = 800, m_Height = 600;
		const char* m_Title = "";
		bool m_IsHidden = false;
		WindowMode m_WindowMode = WindowMode::Windowed;

		std::unique_ptr<GLFWwindow, DestroyglfwWin> m_Window;




	};

}