#include "pch.h"
#include "Window.h"
#include "GLFW/glfw3.h"

#include "Event/Event.h"
namespace FluidEngine
{

	Window::Window(const WindowProps& props)
	{

		Init(props);

	}

	Window::~Window()
	{
		Terminate();
	}

	void Window::Init(const WindowProps& props)
	{
		m_Data.WindowMode = props.Mode;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Ttile = props.Title;
		auto monitor = glfwGetPrimaryMonitor();
		if (m_Data.WindowMode == WindowMode::FullScreen)
		{
			m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Ttile, monitor, NULL);

		}
		else if (m_Data.WindowMode == WindowMode::BorderlessWindow)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			m_Window = glfwCreateWindow(mode->width, mode->height, m_Data.Ttile, monitor, NULL);

		}
		else {

			m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Ttile, NULL, NULL);
		}
		if (m_Window == nullptr)
		{
			Log::GetCoreLogger()->critical("Window has not been created!!!");
			glfwTerminate();
		}
		glViewport(0, 0, m_Data.Width, m_Data.Height);

		glfwSetWindowUserPointer(m_Window, &m_Data);

		//glfwSetFramebufferSizeCallback(m_Window.get(), Window::FrameBufferSizeCallback);


		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.Width = width;
				data.Height = height;
				WindowSizeChangedEvent e(width, height);
				data.EventCallBack(e);


			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowClosedEvent e;
				data.EventCallBack(e);

			}
		);


		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scanCode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(static_cast<KeyCodes>(key), 0);
					data.EventCallBack(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(static_cast<KeyCodes>(key));
					data.EventCallBack(e);
					break;
				}
				case GLFW_REPEAT:
				{
					break;
				}
				default:
					break;
				}

			});

	}
	void Window::SetWidth(int width)
	{
		m_Data.Width = width;
	}

	void Window::SetHeight(int height)
	{
		m_Data.Height = height;
	}

	int Window::GetHeight() const
	{
		return m_Data.Height;
	}

	int Window::GetWidth() const
	{
		return m_Data.Width;
	}

	void Window::SetWindowSize(int width, int height)
	{
		m_Data.Width = width;
		m_Data.Height = height;

	}

	void Window::OnUpdate()
	{

	}

	GLFWwindow* Window::GetWindow()
	{
		return m_Window;
	}

	void Window::OnEvent(IEvent& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowSizeChangedEvent>(std::bind(&Window::OnWindowSizeChanged, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowClosedEvent>(std::bind(&Window::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Window::OnKeyPressed, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&Window::OnKeyReleased, this, std::placeholders::_1));
	}

	bool Window::OnWindowSizeChanged(WindowSizeChangedEvent& e)
	{

		glViewport(0, 0, e.GetWdith(), e.GetHeight());
		return true;
	}

	bool Window::OnWindowClose(WindowClosedEvent& e)
	{
		glfwSetWindowShouldClose(m_Window, 1);
		Log::GetCoreLogger()->info("Window closed");
		return true;
	}

	bool Window::OnKeyPressed(KeyPressedEvent& e)
	{
		Log::GetCoreLogger()->info(e.ToString());
		return true;
	}

	bool Window::OnKeyReleased(KeyReleasedEvent& e)
	{
		Log::GetCoreLogger()->info(e.ToString());
		return true;
	}

	void Window::Terminate()
	{
		glfwDestroyWindow(m_Window);
	}


}