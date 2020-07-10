#pragma once
#include <glad/glad.h>
#include <memory>
#include "Window.h"
#include "Event/IEvent.h"
#include "GameTimer.h"
#include "Renderer.h"
#include "ImguiPanel.h"
#include "GeometryGenerator.h"
namespace FluidEngine
{

	class Application
	{
	public:
		int Init(int majorVer, int minorVer);
		void MainLoop();

	protected:
		void Terminate();

	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> m_Renderer;
		int m_GlfwMinorVersion = 0;
		int m_GlfwMajorVersion = 4;

		GeometryGenerator m_GeomGenerator;
	};
} // namespace FluidEngine
