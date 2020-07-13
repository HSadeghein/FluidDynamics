#include "pch.h"

#include "ImguiPanel.h"
namespace FluidEngine
{
	ImGuiPanel::ImGuiPanel(GLFWwindow* window)
	{
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(m_Glsl_Version);
		ImGui::StyleColorsDark();
	}

	ImGuiPanel::~ImGuiPanel() 
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiPanel::RenderImguiFrame(Window* window, glm::mat4& model, glm::mat4& view)
	{
		int display_w, display_h;
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		
		ImGui::NewFrame();
		{
			static glm::vec3 translateCamera = glm::vec3(0.0);
			static glm::vec3 translateObject = glm::vec3(0.0);

			ImGui::InputFloat3("Camera Position", &translateCamera[0]);
			view = glm::translate(glm::mat4(1.0), -translateCamera);
			ImGui::InputFloat3("Object Position", &translateObject[0]);
			model = glm::translate(glm::mat4(1.0), translateObject);
		}
		ImGui::Render();
		glfwGetFramebufferSize(window->GetWindow(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
	}

	void ImGuiPanel::DrawImgui()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
} // namespace FluidEngine