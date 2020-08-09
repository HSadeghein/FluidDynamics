#include "pch.h"

#include "Application.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderControler.h"
#include "Object.h"
#include "Material.h"
namespace FluidEngine
{
	Application* Application::m_AppInstance = nullptr;
	void error_call_back(int error, const char* description)
	{
		Log::GetCoreLogger()->error("Error: {}", description);
	}

	Application& Application::Get()
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
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		glfwMakeContextCurrent(m_Window->GetWindow());

		//FPS cap
		glfwSwapInterval(0);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			FluidEngine::Log::GetCoreLogger()->error("Glad was not loaded correctly");
			return -1;
		}

		m_LastMousePos = glm::vec2(m_Window->GetWidth() / 2, m_Window->GetHeight() / 2);

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

			std::unique_ptr<Mesh> InstancedMesh = std::make_unique<Mesh>(m_GeomGenerator.CreateBox(10, 10, 10, 1));
			std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>(m_GeomGenerator.CreateBox(3, 5, 3, 1));
			m_Renderer = std::make_unique<Renderer>(m_Window.get());
			m_Renderer->SetCamera(CameraType::Perspective, 45, (float)(width / height), 0.01, 1000.0f);
			std::shared_ptr<Material> material1 = std::move(m_Renderer->CreateMaterial("material1", "shader/vertex.vert", "shader/pixel.frag", "res/image/stoke.jpg", glm::vec4(1), true));
			std::shared_ptr<Material> material2 = std::move(m_Renderer->CreateMaterial("material2", "shader/vertex.vert", "shader/pixel.frag", "res/image/stoke.jpg", glm::vec4(0.5), true));
			m_Renderer->SetUpGPUInstancing(InstancedMesh.get(), 2000, material1);
			//m_Renderer->SetUpGPUInstancing(mesh.get(), 2, material2);
			/*std::shared_ptr<Material> material2 = std::move(m_Renderer->CreateMaterial("material2", "shader/vertex.vert", "shader/pixel.frag", "res/image/stoke.jpg", glm::vec4(1), false));
			std::unique_ptr<Object> object = std::make_unique<Object>(mesh.get(), "Object1", material2);
			m_Renderer->InstertObject(object.get());*/
			while (!glfwWindowShouldClose(m_Window->GetWindow()))
			{
				glfwPollEvents();


				m_Renderer->Tick();
				m_Renderer->CalculateFrameStats();
				m_Renderer->RenderImgui(m_Window.get());
				m_Renderer->Clear();




				m_Renderer->Draw();


				glfwSwapBuffers(m_Window->GetWindow());

			}
		}
		Terminate();
	}

	void Application::OnEvent(IEvent& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowSizeChangedEvent>(std::bind(&Application::OnWindowSizeChanged, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowClosedEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Application::OnKeyPressed, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&Application::OnKeyReleased, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyRepeatedEvent>(std::bind(&Application::OnKeyRepeated, this, std::placeholders::_1));
		dispatcher.Dispatch<LeftMouseButtonPressed>(std::bind(&Application::OnLeftMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.Dispatch<RightMouseButtonPressed>(std::bind(&Application::OnRightMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.Dispatch<RightMouseButtonReleased>(std::bind(&Application::OnRightMouseButtonReleased, this, std::placeholders::_1));
		dispatcher.Dispatch<LeftMouseButtonReleased>(std::bind(&Application::OnLeftMouseButtonReleased, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseMoved>(std::bind(&Application::OnMouseMoved, this, std::placeholders::_1));
	}


	bool Application::OnWindowSizeChanged(WindowSizeChangedEvent& e)
	{

		glViewport(0, 0, e.GetWdith(), e.GetHeight());
		return true;
	}

	bool Application::OnWindowClose(WindowClosedEvent& e)
	{
		glfwSetWindowShouldClose(m_Window->GetWindow(), 1);
		Log::GetCoreLogger()->info("Window closed");
		return true;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		Log::GetCoreLogger()->info(e.ToString());
		if (e.GetKeyCode() == KeyCodes::Escape)
		{
			WindowClosedEvent closedEvent;
			OnWindowClose(closedEvent);
		}
		else if (e.GetKeyCode() == KeyCodes::W)
		{
			glm::vec3 pos = m_Renderer->GetCamera()->GetCameraPosition();
			glm::vec3 forward = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->Forward();
			pos += forward;
			m_Renderer->GetCamera()->SetPosition(pos);

		}
		else if (e.GetKeyCode() == KeyCodes::S)
		{
			glm::vec3 pos = m_Renderer->GetCamera()->GetCameraPosition();
			glm::vec3 forward = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->Forward();
			pos -= forward;
			m_Renderer->GetCamera()->SetPosition(pos);
		}
		return true;
	}

	bool Application::OnKeyReleased(KeyReleasedEvent& e)
	{
		Log::GetCoreLogger()->info(e.ToString());
		return true;
	}

	bool Application::OnKeyRepeated(KeyRepeatedEvent& e)
	{
		if (e.GetKeyCode() == KeyCodes::W)
		{
			glm::vec3 pos = m_Renderer->GetCamera()->GetCameraPosition();
			glm::vec3 forward = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->Forward();
			pos += forward;
			m_Renderer->GetCamera()->SetPosition(pos);

		}
		else if (e.GetKeyCode() == KeyCodes::S)
		{
			glm::vec3 pos = m_Renderer->GetCamera()->GetCameraPosition();
			glm::vec3 forward = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->Forward();
			pos -= forward;
			m_Renderer->GetCamera()->SetPosition(pos);
		}
		return true;
	}

	bool Application::OnRightMouseButtonPressed(RightMouseButtonPressed& e)
	{
		Log::GetCoreLogger()->info(e.ToString());
		m_RightMouseButtonClikced = true;
		return true;
	}

	bool Application::OnLeftMouseButtonPressed(LeftMouseButtonPressed& e)
	{
		Log::GetCoreLogger()->info(e.ToString());
		m_LeftMouseButtonClikced = true;
		return true;
	}

	bool Application::OnMouseMoved(MouseMoved& e)
	{
		float dx = glm::radians(0.15f * static_cast<float>(e.GetX() - m_LastMousePos.x));
		float dy = glm::radians(0.15f * static_cast<float>(e.GetY() - m_LastMousePos.y));
		if (m_RightMouseButtonClikced)
		{

			//m_HorizentalAngle += GameTimer::GetReference()->DeltaTime() * float(m_Window->GetWidth() / 2 - e.GetX());
			//m_VerticalAngle += GameTimer::GetReference()->DeltaTime() * float(m_Window->GetHeight() / 2 - e.GetY());
			m_HorizentalAngle -= dx;
			m_VerticalAngle -= dy;

			// Right vector
			glm::vec3 right = glm::vec3(
				sin(m_HorizentalAngle - 3.14f / 2.0f),
				0,
				cos(m_HorizentalAngle - 3.14f / 2.0f)
			);
			glm::vec3 direction = glm::vec3(glm::cos(m_VerticalAngle) * glm::sin(m_HorizentalAngle), glm::sin(m_VerticalAngle), glm::cos(m_VerticalAngle) * glm::cos(m_HorizentalAngle));
			glm::vec3 up = glm::cross(right, direction);
			//m_Renderer->GetCamera()->SetPosition(eyePos);
			static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->SetForward(direction);
			static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->SetUp(up);

			float pitch = glm::acos(glm::dot(up, glm::vec3(0, 1, 0)));
			float yaw = glm::acos(glm::dot(right, glm::vec3(-1, 0, 0)));

			static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->SetRotation(glm::vec3(glm::degrees(pitch) * glm::sign(direction.y), glm::degrees(yaw) * glm::sign(direction.x), 0));

		}
		else if (m_LeftMouseButtonClikced)
		{

			m_Theta -= dx;
			m_Phi += dy;
			m_Phi = glm::clamp(m_Phi, 0.1f, glm::pi<float>() - 0.1f);
			m_EyePos.x = m_Radius * glm::sin(m_Phi) * glm::cos(m_Theta);
			m_EyePos.z = m_Radius * glm::sin(m_Phi) * glm::sin(m_Theta);
			m_EyePos.y = m_Radius * glm::cos(m_Phi);


			//eyePos.z -= m_Radius;
			m_Renderer->GetCamera()->SetPosition(m_EyePos);

		}
		m_LastMousePos.x = e.GetX();
		m_LastMousePos.y = e.GetY();
		return true;
	}

	bool Application::OnRightMouseButtonReleased(RightMouseButtonReleased& e)
	{
		m_RightMouseButtonClikced = false;
		return true;
	}

	bool Application::OnLeftMouseButtonReleased(LeftMouseButtonReleased& e)
	{
		m_LeftMouseButtonClikced = false;
		return true;
	}



	void Application::Terminate()
	{
		m_Renderer.reset();
		m_Window->Terminate();
		glfwTerminate();
	}
} // namespace FluidEngine
