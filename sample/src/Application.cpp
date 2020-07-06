#include "Application.h"
#include <functional>
namespace FluidEngine {



	void error_call_back(int error, const char* description)
	{
		Log::GetCoreLogger()->error("Error: {}", description);
	}
	int Application::Init(int majorVer, int minorVer)
	{

		glfwSetErrorCallback(error_call_back);
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		WindowProps props(600, 800, "Hassan");
		m_Window = std::make_unique<Window>(props);
		//std bind --> bind a function or a member to a another function
		//in this line we binded applicaion::onevent function, the first aurgument indicates the concept of the function, second argument indicates which function exactly we want to use
		//the third argument indicates we want to pass a variables or some predefined value.
		m_Window->SetEventCallback(std::bind(&Window::OnEvent, m_Window.get(), std::placeholders::_1));
		glfwMakeContextCurrent(m_Window->GetWindow());


		//FPS cap
		glfwSwapInterval(0);


		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			FluidEngine::Log::GetCoreLogger()->error("Glad was not loaded correctly");
			return -1;
		}

		m_Timer.Reset();
		return 1;
	}

	void Application::MainLoop()
	{
		while (!glfwWindowShouldClose(m_Window->GetWindow()))
		{
			m_Timer.Tick();
			glfwSwapBuffers(m_Window->GetWindow());
			glfwPollEvents();
			//auto dt = m_Timer.DeltaTime();
			//Log::GetCoreLogger()->info("delta time is {}", dt);
			CalculateFrameStats();
		}
		Terminate();
	}
	void Application::Terminate()
	{
		m_Window->Terminate();
		glfwTerminate();
	}

	void Application::CalculateFrameStats()
	{
		static int frameCount = 0;
		static float timeElapsed = 0;

		frameCount++;

		if ((m_Timer.TotalTime() - timeElapsed) >= 1.0f)
		{
			float fps = (float)frameCount;
			float mspf = 1000.0f / fps;

			Log::GetCoreLogger()->info("FPS is {}", fps);
			Log::GetCoreLogger()->info("Frame per milisecond is {}", mspf);

			frameCount = 0;
			timeElapsed += 1.0f;
		}
	}

}

