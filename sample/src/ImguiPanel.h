#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Window.h"

namespace FluidEngine {
	class ImGuiPanel
	{
	public:
		ImGuiPanel(){}
		~ImGuiPanel() {}
		void InitiateImgui(GLFWwindow* window);
		void RenderImguiFrame();
		void AssignImguiViewport(GLFWwindow* window);
		void DrawImgui();
		void TerminateImgui();
	private:
		const char* m_Glsl_Version = "#version 130";
		bool m_Show_Demo_Window = true;
		bool m_Show_Another_Window = false;
		ImVec4 m_ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	};
}