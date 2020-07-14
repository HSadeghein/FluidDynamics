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

	void ImGuiPanel::RenderImguiFrame(Window* window, Transform* transform, Camera* camera)
	{
		int display_w, display_h;
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		{
			static glm::vec3 positionCamera = glm::vec3(0.0);
			static glm::vec3 position = glm::vec3(0.0);
			static glm::vec3 rotation = glm::vec3(0.0);
			static glm::vec3 scale = glm::vec3(1.0);


			if (camera->GetCameraType() == CameraType::Orthogonal)
			{
				ImGui::Text("Orthogonal Camera : ");
				ImGui::InputFloat3("Camera Position", &positionCamera[0]);
				camera->SetPosition(positionCamera);
			}

			ImGui::Text("Transform : ");
			ImGui::InputFloat3("Position", &position[0]);
			ImGui::InputFloat3("Rotation", &rotation[0]);
			ImGui::InputFloat3("Scale", &scale[0]);
			transform->SetPosition(position);
			transform->SetRotation(rotation);
			transform->SetScale(scale);
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