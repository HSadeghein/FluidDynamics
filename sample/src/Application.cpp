#include "pch.h"

#include "Application.h"
#include "Renderer.h"

namespace FluidEngine
{
	Application *Application::m_AppInstance = nullptr;
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

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			std::unique_ptr<Mesh> InstancedMesh = std::make_unique<Mesh>(m_GeomGenerator.CreateSphere(5, 50, 50));
			m_Renderer = std::make_unique<Renderer>(m_Window.get());
			m_Renderer->SetCamera(CameraType::Perspective, 45, (float)(width / height), 0.01, 1000.0f);
			m_Renderer->SetLight(glm::vec3(0, 10, -10), glm::vec4(1), 0.1, 0.5);
			std::shared_ptr<Material> material1 = std::move(m_Renderer->CreateMaterial("material1", "shader/vertex.vert", "shader/pixel.frag", "", glm::vec4(1), true));
			m_Renderer->SetUpGPUInstancing(InstancedMesh.get(), 10, material1);

			while (!glfwWindowShouldClose(m_Window->GetWindow()))
			{
				glfwPollEvents();

				if (m_LeftMouseButtonClicked)
				{
					glm::vec3 pos = m_Renderer->GetCamera()->GetCameraPosition();
					auto camera = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera());
					glm::vec3 forward = camera->GetForward();
					pos += forward * m_MouseSpeed;
					camera->SetPosition(pos);


					// Right vector
					glm::vec3 right = glm::vec3(
						sin(m_HorizentalAngle - 3.14f / 2.0f),
						0,
						cos(m_HorizentalAngle - 3.14f / 2.0f));
					glm::vec3 direction = glm::vec3(glm::cos(m_VerticalAngle) * glm::sin(m_HorizentalAngle), glm::sin(m_VerticalAngle), glm::cos(m_VerticalAngle) * glm::cos(m_HorizentalAngle));
					glm::vec3 up = glm::cross(right, direction);

					camera->SetForward(direction);
					camera->SetUp(up);
					camera->SetRight(right);
					float pitch = glm::acos(glm::dot(up, glm::vec3(0, 1, 0)));
					float yaw = glm::acos(glm::dot(right, glm::vec3(-1, 0, 0)));

					camera->SetRotation(glm::vec3(glm::degrees(pitch) * glm::sign(direction.y), glm::degrees(yaw) * glm::sign(direction.x), 0));

				}
				m_Renderer->Tick();
				m_Renderer->CalculateFrameStats();
				m_Renderer->RenderImgui(m_Window.get());
				m_Renderer->Clear();

				//Log::GetCoreLogger()->info("is fouced is {0}", ImGui::IsAnyWindowFocused());
				m_Renderer->Draw();

				glfwSwapBuffers(m_Window->GetWindow());
			}
		}
		Terminate();
	}

	void Application::OnEvent(IEvent &e)
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

	bool Application::OnWindowSizeChanged(WindowSizeChangedEvent &e)
	{

		glViewport(0, 0, e.GetWdith(), e.GetHeight());
		return true;
	}

	bool Application::OnWindowClose(WindowClosedEvent &e)
	{
		glfwSetWindowShouldClose(m_Window->GetWindow(), 1);
		Log::GetCoreLogger()->info("Window closed");
		return true;
	}

	bool Application::OnKeyPressed(KeyPressedEvent &e)
	{
		if (e.GetKeyCode() == KeyCodes::Escape)
		{
			WindowClosedEvent closedEvent;
			OnWindowClose(closedEvent);
		}
		if (!ImGui::IsAnyWindowFocused())
		{
			Log::GetCoreLogger()->info(e.ToString());

			if (e.GetKeyCode() == KeyCodes::W)
			{
				glm::vec3 pos = m_Renderer->GetCamera()->GetCameraPosition();
				glm::vec3 forward = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->GetForward();
				pos += forward;
				m_Renderer->GetCamera()->SetPosition(pos);
			}
			else if (e.GetKeyCode() == KeyCodes::S)
			{
				glm::vec3 pos = m_Renderer->GetCamera()->GetCameraPosition();
				glm::vec3 forward = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->GetForward();
				pos -= forward;
				m_Renderer->GetCamera()->SetPosition(pos);
			}
			else if (e.GetKeyCode() == KeyCodes::A)
			{
				glm::vec3 pos = m_Renderer->GetCamera()->GetCameraPosition();
				glm::vec3 right = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->GetRight();
				pos -= right;
				m_Renderer->GetCamera()->SetPosition(pos);
			}
			else if (e.GetKeyCode() == KeyCodes::D)
			{
				glm::vec3 pos = m_Renderer->GetCamera()->GetCameraPosition();
				glm::vec3 right = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->GetRight();
				pos += right;
				m_Renderer->GetCamera()->SetPosition(pos);
			}
		}
		return true;
	}

	bool Application::OnKeyReleased(KeyReleasedEvent &e)
	{
		Log::GetCoreLogger()->info(e.ToString());
		return true;
	}

	bool Application::OnKeyRepeated(KeyRepeatedEvent &e)
	{
		if (!ImGui::IsAnyWindowFocused())
		{
			if (e.GetKeyCode() == KeyCodes::W)
			{
				glm::vec3 pos = m_Renderer->GetCamera()->GetCameraPosition();
				glm::vec3 forward = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->GetForward();
				pos += forward;
				m_Renderer->GetCamera()->SetPosition(pos);
			}
			else if (e.GetKeyCode() == KeyCodes::S)
			{
				glm::vec3 pos = m_Renderer->GetCamera()->GetCameraPosition();
				glm::vec3 forward = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->GetForward();
				pos -= forward;
				m_Renderer->GetCamera()->SetPosition(pos);
			}
			else if (e.GetKeyCode() == KeyCodes::A)
			{
				glm::vec3 pos = m_Renderer->GetCamera()->GetCameraPosition();
				glm::vec3 right = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->GetRight();
				pos -= right;
				m_Renderer->GetCamera()->SetPosition(pos);
			}
			else if (e.GetKeyCode() == KeyCodes::D)
			{
				glm::vec3 pos = m_Renderer->GetCamera()->GetCameraPosition();
				glm::vec3 right = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera())->GetRight();
				pos += right;
				m_Renderer->GetCamera()->SetPosition(pos);
			}
		}
		return true;
	}

	bool Application::OnRightMouseButtonPressed(RightMouseButtonPressed &e)
	{
		if (!ImGui::IsAnyWindowFocused())
		{
			Log::GetCoreLogger()->info(e.ToString());
			m_RightMouseButtonClicked = true;
		}
		return true;
	}

	bool Application::OnLeftMouseButtonPressed(LeftMouseButtonPressed &e)
	{
		if (!ImGui::IsAnyWindowFocused())
		{
			m_LeftMouseButtonClicked = true;
		}
		return true;
	}


	bool Application::OnMouseMoved(MouseMoved &e)
	{

		float dx = glm::radians(0.15f * static_cast<float>(e.GetX() - m_LastMousePos.x));
		float dy = glm::radians(0.15f * static_cast<float>(e.GetY() - m_LastMousePos.y));

		glm::vec2 center = glm::vec2(m_Window->GetWidth() / 2, m_Window->GetHeight() / 2);
		m_DistanceToCenter = glm::vec2(e.GetX() - center.x, -e.GetY() + center.y);
		m_DistanceToCenter /= glm::vec2(m_Window->GetWidth(), m_Window->GetHeight());

		m_MouseSpeed = m_DistanceToCenter.y / 10.0f;
		//m_MouseSpeed = glm::clamp(m_MouseSpeed, -5.0f, +5.0f);
		if (!ImGui::IsAnyWindowFocused())
		{
			if (m_RightMouseButtonClicked || m_LeftMouseButtonClicked)
			{

				m_HorizentalAngle -= dx;
			

			}
			if (m_RightMouseButtonClicked)
			{
				m_VerticalAngle -= dy;


				// Right vector
				glm::vec3 right = glm::vec3(
					sin(m_HorizentalAngle - 3.14f / 2.0f),
					0,
					cos(m_HorizentalAngle - 3.14f / 2.0f));
				glm::vec3 direction = glm::vec3(glm::cos(m_VerticalAngle) * glm::sin(m_HorizentalAngle), glm::sin(m_VerticalAngle), glm::cos(m_VerticalAngle) * glm::cos(m_HorizentalAngle));
				glm::vec3 up = glm::cross(right, direction);

				auto camera = static_cast<PerspectiveCamera*>(m_Renderer->GetCamera());
				camera->SetForward(direction);
				camera->SetUp(up);
				camera->SetRight(right);
				float pitch = glm::acos(glm::dot(up, glm::vec3(0, 1, 0)));
				float yaw = glm::acos(glm::dot(right, glm::vec3(-1, 0, 0)));

				camera->SetRotation(glm::vec3(glm::degrees(pitch) * glm::sign(direction.y), glm::degrees(yaw) * glm::sign(direction.x), 0));
			}
		}
		m_LastMousePos.x = e.GetX();
		m_LastMousePos.y = e.GetY();
		return true;
	}

	bool Application::OnRightMouseButtonReleased(RightMouseButtonReleased &e)
	{
		if (!ImGui::IsAnyWindowFocused())
		{
			m_RightMouseButtonClicked = false;
		}
		return true;
	}

	bool Application::OnLeftMouseButtonReleased(LeftMouseButtonReleased &e)
	{
		if (!ImGui::IsAnyWindowFocused())
		{
			m_LeftMouseButtonClicked = false;
			m_MouseSpeed = 0;
		}
		return true;
	}

	void Application::Terminate()
	{
		m_Renderer.reset();
		m_Window->Terminate();
		glfwTerminate();
	}
} // namespace FluidEngine
