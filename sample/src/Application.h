#pragma once
#define GLFW_INCLUDE_NONE
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>


#include <memory>
#include "Event/IEvent.h"
#include "Renderer.h"
#include "GeometryGenerator.h"

#include "Window.h"

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

		GeometryGenerator m_GeomGenerator;

	};
}
