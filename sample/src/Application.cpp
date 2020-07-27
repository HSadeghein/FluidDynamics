#include "pch.h"

#include "Application.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderControler.h"
#include "Object.h"
#include "Material.h"

namespace FluidEngine
{
	Application *Application::m_AppInstance = nullptr;
	Application::Application()
	{
	}
	void error_call_back(int error, const char *description)
	{
		Log::GetCoreLogger()->error("Error: {}", description);
	}

	Application &Application::Get()
	{
		if (m_AppInstance == nullptr)
		{
			m_AppInstance = new Application();
		}
		return *m_AppInstance;
	}

	int Application::Init(int majorVer, int minorVer)
	{
		glfwSetErrorCallback(error_call_back);
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		WindowProps props(800, 600, "Cumrun");
		m_Window = std::make_unique<Window>(props);
		//m_Window->RegisterApplication(shared_from_this());

		//std bind --> bind a function or a member to a another function
		//in this line we binded window::onevent function, the first aurgument indicates the concept of the function, second argument indicates which function exactly we want to use
		//the third argument indicates weather we want to pass a variables or some predefined value.
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
			int height = m_Window->GetHeight();
			int width = m_Window->GetWidth();
			auto meshData = m_GeomGenerator.CreateBox(10, 10, 10, 3);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			m_Renderer = std::make_unique<Renderer>(meshData.Vertices, meshData.Indices, m_Window.get());
			== == == =
						 std::unique_ptr<Mesh> InstancedMesh = std::make_unique<Mesh>(m_GeomGenerator.CreateBox(10, 10, 10, 1));
			std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>(m_GeomGenerator.CreateBox(3, 5, 3, 1));
			m_Renderer = std::make_unique<Renderer>(m_Window.get());
			m_Renderer->SetCamera(CameraType::Perspective, 45, (float)(width / height), 0.01, 1000.0f);
			std::shared_ptr<Material> material1 = std::move(m_Renderer->CreateMaterial("material1", "shader/vertex.vert", "shader/pixel.frag", "res/image/stoke.jpg", glm::vec4(1), true));
			std::shared_ptr<Material> material2 = std::move(m_Renderer->CreateMaterial("material2", "shader/vertex.vert", "shader/pixel.frag", "res/image/stoke.jpg", glm::vec4(0.5), true));
			m_Renderer->SetUpGPUInstancing(InstancedMesh.get(), 2000, material1);
			m_Renderer->SetUpGPUInstancing(mesh.get(), 2, material2);
			/*std::shared_ptr<Material> material2 = std::move(m_Renderer->CreateMaterial("material2", "shader/vertex.vert", "shader/pixel.frag", "res/image/stoke.jpg", glm::vec4(1), false));
			std::unique_ptr<Object> object = std::make_unique<Object>(mesh.get(), "Object1", material2);
			m_Renderer->InstertObject(object.get());*/

			while (!glfwWindowShouldClose(m_Window->GetWindow()))
			{
				m_Renderer->Tick();
				m_Renderer->CalculateFrameStats();
				m_Renderer->RenderImgui(m_Window.get());
				glfwSwapBuffers(m_Window->GetWindow());
				glfwPollEvents();
				m_Renderer->Clear();
				m_Renderer->Draw();
			}
		}
		Terminate();
	}

	void Application::Terminate()
	{
		m_Renderer.reset();
		m_Window->Terminate();
		glfwTerminate();
	}
} // namespace FluidEngine
