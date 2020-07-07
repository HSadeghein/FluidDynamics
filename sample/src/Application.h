#pragma once
#include <glad/glad.h>
#include <memory>
#include "Window.h"
#include "Event/IEvent.h"
#include "GameTimer.h"
#include "ImguiPanel.h"

namespace FluidEngine
{

	class Application
	{
	public:
		int Init(int majorVer, int minorVer);
		void MainLoop();

	protected:
		void DrawGL();
		void Terminate();
		void CalculateFrameStats();

	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<ImGuiPanel> m_Imgui_Panel;
		int m_GlfwMinorVersion = 0;
		int m_GlfwMajorVersion = 4;
		GameTimer m_Timer;
	};
} // namespace FluidEngine
