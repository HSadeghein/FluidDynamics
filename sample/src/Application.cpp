#include "Application.h"

namespace FluidEngine {
	int Application::Init(int minorVer, int majorVer)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_Window = std::make_unique<Window>(800, 600);
		glfwMakeContextCurrent(m_Window->GetWindow());

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			FluidEngine::Log::GetCoreLogger()->error("Glad was not loaded correctly");
			return -1;
		}
		return 1;
	}

	void Application::MainLoop()
	{
		while (!glfwWindowShouldClose(m_Window->GetWindow()))
		{
			glfwSwapBuffers(m_Window->GetWindow());
			glfwPollEvents();
		}
		Terminate();
	}
	void Application::Terminate()
	{
		m_Window->Terminate();
		glfwTerminate();
	}
}

