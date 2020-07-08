#include "ImguiPanel.h"
namespace FluidEngine
{

	void ImGuiPanel::InitiateImgui(GLFWwindow *window)
	{
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(m_Glsl_Version);
		ImGui::StyleColorsDark();
	}
	void ImGuiPanel::RenderImguiFrame(GLFWwindow *window)
	{
		int display_w, display_h;
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");			 // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &m_Show_Demo_Window); // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &m_Show_Another_Window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);			  // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float *)&m_ClearColor); // Edit 3 floats representing a color

			if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		ImGui::Render();
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
	}

	void ImGuiPanel::DrawImgui()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiPanel::TerminateImgui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
} // namespace FluidEngine