#include "Application.h"
#include <functional>
#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderControler.h"

namespace FluidEngine
{
	void error_call_back(int error, const char *description)
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

		return 1;
	}

	void Application::MainLoop()
	{
		{
			const float positions[] = {
				0.5f, 0.5f, 0.0f, 1.0f,
				0.5f, -0.5f, 0.0f, 1.0f,
				-0.5f, -0.5f, 0.0f, 1.0f,
				-0.5f, 0.5f, 0.0f, 1.0};

			unsigned int indices[] = {
				0, 1, 3,
				1, 2, 3};

			VertexArray va;
			VertexBuffer vb(positions, sizeof(positions));
			BufferLayout layout;
			layout.Push<float>(4);
			va.AddBuffer(layout, vb);
			IndexBuffer ib(indices, 6);
			ShaderControler shaderControler;
			shaderControler.ConvAllHlslToGlsl();
			shaderControler.AddShader({"shader/vertex.vert", GL_VERTEX_SHADER, true});
			shaderControler.AddShader({"shader/pixel.frag", GL_FRAGMENT_SHADER, true});
			shaderControler.CreateShaderProgram();
			shaderControler.UseShaderProgram();
			ImGuiPanel panel;
			panel.InitiateImgui(m_Window->GetWindow());
			Renderer renderer;

			while (!glfwWindowShouldClose(m_Window->GetWindow()))
			{
				renderer.Tick();
				glfwPollEvents();
				//auto dt = m_Timer.DeltaTime();
				//Log::GetCoreLogger()->info("delta time is {}", dt);
				renderer.CalculateFrameStats();
				panel.RenderImguiFrame(m_Window->GetWindow());
				glfwSwapBuffers(m_Window->GetWindow());
				renderer.Clear();
				renderer.Draw(va, ib, panel);
			}
			panel.TerminateImgui();
		}
		Terminate();
	}

	void Application::Terminate()
	{
		m_Window->Terminate();
		glfwTerminate();
	}
} // namespace FluidEngine
