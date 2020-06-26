#pragma once
#include <glad/glad.h>
#include <memory>
#include "Window.h"
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
		std::unique_ptr<Window> m_Window;
		int m_GlfwMinorVersion = 0;
		int m_GlfwMajorVersion = 4;

	};
}

