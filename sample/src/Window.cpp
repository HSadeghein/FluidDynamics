#include "pch.h"

#include "Window.h"

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
		else
		{

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


								  }
		);

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
								   KeyRepeatedEvent e(static_cast<KeyCodes>(key));
								   data.EventCallBack(e);
								   break;
							   }
							   default:
								   break;
							   }

						   }
		);

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mode)
								   {
									   WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
									   if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
									   {
										   double xPos, yPos;
										   glfwGetCursorPos(window, &xPos, &yPos);
										   RightMouseButtonPressed e(xPos, yPos);
										   data.EventCallBack(e);
									   }
									   else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
									   {
										   double xPos, yPos;
										   glfwGetCursorPos(window, &xPos, &yPos);
										   LeftMouseButtonPressed e(xPos, yPos);
										   data.EventCallBack(e);
									   }
									   else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
									   {
										   RightMouseButtonReleased e;
										   data.EventCallBack(e);
									   }
									   else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
									   {
										   LeftMouseButtonReleased e;
										   data.EventCallBack(e);
									   }
								   }
		);

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
								 {
									 WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
									 MouseMoved e(xPos, yPos);
									 data.EventCallBack(e);
								 }
		);

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

	//void Window::OnEvent(IEvent& e)
	//{
	//	EventDispatcher dispatcher(e);

	//	dispatcher.Dispatch<WindowSizeChangedEvent>(std::bind(&Window::OnWindowSizeChanged, this, std::placeholders::_1));
	//	dispatcher.Dispatch<WindowClosedEvent>(std::bind(&Window::OnWindowClose, this, std::placeholders::_1));
	//	dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Window::OnKeyPressed, this, std::placeholders::_1));
	//	dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&Window::OnKeyReleased, this, std::placeholders::_1));
	//	dispatcher.Dispatch<LeftMouseButtonPressed>(std::bind(&Window::OnLeftMouseButtonPressed, this, std::placeholders::_1));
	//	dispatcher.Dispatch<RightMouseButtonPressed>(std::bind(&Window::OnRightMouseButtonPressed, this, std::placeholders::_1));
	//	dispatcher.Dispatch<MouseMoved>(std::bind(&Window::OnMouseMoved, this, std::placeholders::_1));

	//}

	//bool Window::OnWindowSizeChanged(WindowSizeChangedEvent& e)
	//{

	//	glViewport(0, 0, e.GetWdith(), e.GetHeight());
	//	return true;
	//}

	//bool Window::OnWindowClose(WindowClosedEvent& e)
	//{
	//	glfwSetWindowShouldClose(m_Window, 1);
	//	Log::GetCoreLogger()->info("Window closed");
	//	return true;
	//}

	//bool Window::OnKeyPressed(KeyPressedEvent& e)
	//{
	//	Log::GetCoreLogger()->info(e.ToString());
	//	if (e.GetKeyCode() == KeyCodes::Escape)
	//	{
	//		WindowClosedEvent closedEvent;
	//		OnWindowClose(closedEvent);
	//	}
	//	return true;
	//}

	//bool Window::OnKeyReleased(KeyReleasedEvent& e)
	//{
	//	Log::GetCoreLogger()->info(e.ToString());
	//	return true;
	//}

	//bool Window::OnRightMouseButtonPressed(RightMouseButtonPressed& e)
	//{
	//	Log::GetCoreLogger()->info(e.ToString());
	//	return true;
	//}

	//bool Window::OnLeftMouseButtonPressed(LeftMouseButtonPressed& e)
	//{
	//	Log::GetCoreLogger()->info(e.ToString());
	//	return true;
	//}

	//bool Window::OnMouseMoved(MouseMoved& e)
	//{
	//	Log::GetCoreLogger()->info(e.ToString());
	//	if (auto spt = m_Application.lock())
	//	{
	//		//Log::GetCoreLogger()->info("Camera Position {0}", spt->m_Renderer->m_Camera->Position().x);
	//	}
	//	return true;
	//}

	void Window::Terminate()
	{
		glfwDestroyWindow(m_Window);
	}


}