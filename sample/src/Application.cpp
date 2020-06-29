#include "Application.h"

namespace FluidEngine {

	int Application::Init(int minorVer, int majorVer)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		m_Window = std::shared_ptr<Window>(new Window(800, 600));
		m_Imgui_Panel = std::make_unique<ImGuiPanel>(m_Window);
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
		m_Imgui_Panel->InitiateImgui();

		while (!glfwWindowShouldClose(m_Window->GetWindow()))
		{
			glfwPollEvents();
			m_Imgui_Panel->RenderImguiFrame();
			glfwSwapBuffers(m_Window->GetWindow());
			m_Imgui_Panel->ClearImguiFrame();
		}
		m_Imgui_Panel->TerminateImgui();
		Terminate();

	}

	void Application::Terminate()
	{
		m_Window->Terminate();
		glfwTerminate();
	}
}

