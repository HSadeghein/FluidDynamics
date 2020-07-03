#pragma once
#include <glad/glad.h>
#include <memory>
#include "Window.h"
#include "ImguiPanel.h"
#include "HlslToGlslConverter.h"
#include <Windows.h>

namespace FluidEngine
{

	class Application 
	{
	public:
		int Init(int minorVer, int majorVer);
		void MainLoop();
		void ConvAllHlslToGlsl();
		void ConvHlslToGlsl(LPCWSTR sourceName, LPCWSTR targetSPVName, LPCWSTR targetName, LPCWSTR glslangArgs[2], 
			LPCWSTR spirvArgs[2]);
	protected:
		void ConfigureGL(GLuint* program, GLuint* VAO, GLuint* VBO);
		void DrawGL(GLuint program, GLuint VAO, GLuint VBO);
		void Terminate();
		GLuint CompileProgram();
		GLuint LoadGlslShader(const char* filename, GLenum shaderType, bool checkErrors);
	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<ImGuiPanel> m_Imgui_Panel;
		std::unique_ptr<HlslToGlslConverter> m_HlslToGlslConverter;
		int m_GlfwMinorVersion = 0;
		int m_GlfwMajorVersion = 4;
		LPCWSTR glslangExeDir = L"..\\SPIRV-Cross\\external\\glslang-build\\output\\bin\\glslangValidator.exe";
		LPCWSTR spirvCrossExeDir = L"..\\SPIRV-Cross\\build\\Debug\\spirv-cross.exe";
	};
}

