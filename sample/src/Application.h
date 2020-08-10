#pragma once
#define GLFW_INCLUDE_NONE
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>


#include <memory>
#include "Event/IEvent.h"
#include "Renderer.h"
#include "GeometryGenerator.h"
#include <glm/gtx/vector_angle.hpp>
#include "Window.h"
#include <cmath>
namespace FluidEngine
{
	class Window;
	class Application
	{
	public:
		Application(Application& app) = delete;
		void operator=(const Application&) = delete;


		int Init(int majorVer, int minorVer);

		void MainLoop();

		Window* GetWindow() { return m_Window.get(); }

		Renderer* GetRenderer() { return m_Renderer.get(); }


		static Application& Get();
	protected:
		friend class Window;

		Application() {}

		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> m_Renderer;

		void Terminate();

	private:
		static Application* m_AppInstance;
		int m_GlfwMinorVersion = 0;
		int m_GlfwMajorVersion = 4;
		glm::vec2 m_LastMousePos;
		float m_Theta = 1.5f * glm::pi<float>();
		float m_Phi = .2f * glm::pi<float>();
		float m_Radius = 50.0f;

		float m_HorizentalAngle = 0.0f;
		float m_VerticalAngle = 0.0f;

		GeometryGenerator m_GeomGenerator;


		void OnEvent(IEvent& e);


		bool OnWindowSizeChanged(WindowSizeChangedEvent& e);

		bool OnWindowClose(WindowClosedEvent& e);

		bool OnKeyPressed(KeyPressedEvent& e);

		bool OnKeyReleased(KeyReleasedEvent& e);

		bool OnKeyRepeated(KeyRepeatedEvent& e);

		bool OnRightMouseButtonPressed(RightMouseButtonPressed& e);

		bool OnLeftMouseButtonPressed(LeftMouseButtonPressed& e);

		bool OnLeftMouseButtonReleased(LeftMouseButtonReleased& e);

		bool OnRightMouseButtonReleased(RightMouseButtonReleased& e);


		bool OnMouseMoved(MouseMoved& e);




		glm::vec2 m_DistanceToCenter = glm::vec2(0, 0);
		float m_MouseSpeed = 1.0f;
		bool m_LeftMouseButtonClicked = false;
		bool m_RightMouseButtonClicked = false;
		glm::vec3 m_EyePos = glm::vec3(0, 0, -50.0f);

	};
}
