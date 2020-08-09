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

	void ImGuiPanel::RenderImguiFrame(Window* window, Camera* camera)
	{
		int display_w, display_h;
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		{
			glm::vec3 positionCamera = glm::vec3(0, 0, -50);
		    glm::vec3 rotationCamera = glm::vec3(0.0);
		    float fov = 45;

			if (camera->GetCameraType() == CameraType::Orthogonal)
			{
				ImGui::Text("Orthogonal Camera : ");
				ImGui::InputFloat3("Camera Position", &positionCamera[0]);
				camera->SetPosition(positionCamera);
			}
			else if (camera->GetCameraType() == CameraType::Perspective)
			{
				ImGui::Text("Perspective Camera : ");
				ImGui::InputFloat3("Camera Position", &positionCamera[0]);
				ImGui::InputFloat3("Camera Rotation", &rotationCamera[0]);
				ImGui::InputFloat("Field of View", &fov);
				camera->SetPosition(positionCamera);
				dynamic_cast<PerspectiveCamera*>(camera)->SetFOV(fov);
				dynamic_cast<PerspectiveCamera*>(camera)->SetRotation(rotationCamera);
			}
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