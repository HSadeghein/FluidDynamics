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
		void Terminate();

	private:
		std::unique_ptr<Window> m_Window;
		int m_GlfwMinorVersion = 0;
		int m_GlfwMajorVersion = 4;
	};
} // namespace FluidEngine
