#pragma once
#include <glad/glad.h>
#include <memory>
#include "Window.h"
#include "Event/IEvent.h"
#include "GameTimer.h"
#include "ImguiPanel.h"
#include "HlslToGlslConverter.h"
#include <Windows.h>

namespace FluidEngine
{

	class Application
	{
	public:
		int Init(int majorVer, int minorVer);
		void MainLoop();
		void ConvAllHlslToGlsl();
		void ConvHlslToGlsl(LPCWSTR sourceName, LPCWSTR targetSPVName, LPCWSTR targetName, LPCWSTR glslangArgs[2],
							LPCWSTR spirvArgs[2]);

	protected:
		void DrawGL();
		void Terminate();

		void CalculateFrameStats();

	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<ImGuiPanel> m_Imgui_Panel;
		std::unique_ptr<HlslToGlslConverter> m_HlslToGlslConverter;
		int m_GlfwMinorVersion = 0;
		int m_GlfwMajorVersion = 4;
		GameTimer m_Timer;
		LPCWSTR glslangExeDir = L"..\\vendors\\SPIRV-Cross\\external\\glslang-build\\output\\bin\\glslangValidator.exe";
		LPCWSTR spirvCrossExeDir = L"..\\vendors\\SPIRV-Cross\\build\\Debug\\spirv-cross.exe";
	};
} // namespace FluidEngine
