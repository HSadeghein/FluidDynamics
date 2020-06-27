#include "Window.h"
#include "GLFW/glfw3.h"
namespace FluidEngine
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	Window::Window(int width, int height, WindowMode windowMode)
	{
		m_WindowMode = windowMode;
		auto monitor = glfwGetPrimaryMonitor();
		if (m_WindowMode == WindowMode::FullScreen)
		{
			m_Window = std::unique_ptr<GLFWwindow, DestroyglfwWin>(glfwCreateWindow(width, height, m_Title, monitor, NULL));

		}
		else if (m_WindowMode == WindowMode::BorderlessWindow)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			m_Window = std::unique_ptr<GLFWwindow, DestroyglfwWin>(glfwCreateWindow(mode->width, mode->height, m_Title, monitor, NULL));

		}
		else {

			m_Window = std::unique_ptr<GLFWwindow, DestroyglfwWin>(glfwCreateWindow(width, height, m_Title, NULL, NULL));
		}
		if (m_Window == nullptr)
		{
			Log::GetCoreLogger()->critical("Window has not been created!!!");
			glfwTerminate();
		}

		glViewport(0, 0, 800, 700);
		glfwSetFramebufferSizeCallback(m_Window.get(), framebuffer_size_callback);
	}

	Window::~Window()
	{

	}

	void Window::SetWidth(int width)
	{
		m_Width = width;
	}

	void Window::SetHeight(int height)
	{
		m_Height = height;
	}

	int Window::GetHeight()
	{
		return m_Height;
	}

	int Window::GetWidth()
	{
		return m_Width;
	}

	void Window::SetWindowSize(int width, int height)
	{
		m_Width = width;
		m_Height = height;

	}

	GLFWwindow* Window::GetWindow()
	{
		return m_Window.get();
	}

	void Window::Terminate()
	{
		glfwDestroyWindow(m_Window.get());
	}


}