#pragma once
#include <glad/glad.h>
#include <memory>
#include "Window.h"
#include "ImguiPanel.h"

namespace FluidEngine
{

	class Application 
	{
	public:
		int Init(int minorVer, int majorVer);
		void MainLoop();
	protected:
		void Terminate();
	private:
		std::shared_ptr<Window> m_Window;
		std::unique_ptr<ImGuiPanel> m_Imgui_Panel;
		int m_GlfwMinorVersion = 0;
		int m_GlfwMajorVersion = 4;

	};
}

