#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderControler.h"
#include "ImguiPanel.h"
#include "GameTimer.h"
#include "Camera.h"
#include "Object.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "GPUInstancing.h"
#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"

#define ASSERT(x) \
	if (!(x))     \
		__debugbreak();
#define GL_CHECK_ERROR(x) \
	GlClearErrors();      \
	x;                    \
	ASSERT(GlDisplayError())

void GlClearErrors();
bool GlDisplayError();

namespace FluidEngine
{
	class Renderer
	{
	public:
		Renderer(Window *window);
		~Renderer();
		void Draw();
		void Clear() const;
		void Tick();
		void CalculateFrameStats();
		void RenderImgui(Window *window);
		std::shared_ptr<Material> CreateMaterial(std::string nameID, std::string vertexShader, std::string pixelShader, std::string texturePath, glm::vec4 color, bool isInstancing);
		void SetCamera(CameraType cameraType);
		void SetCamera(CameraType cameraType, float fov, float aspect, float zNear, float zFar);
		void SetUpGPUInstancing(Mesh *mesh, int instanceNumber, std::shared_ptr<Material> material);
		inline glm::mat4 &Projection() { return m_Projection; }
		inline glm::mat4 &View() { return m_View; }

		std::unique_ptr<Camera> m_Camera;

	protected:
		int m_InstanceNumber;
		int m_WindowHeight, m_WindowWidth;
		GameTimer m_Timer;
		std::vector<std::unique_ptr<GPUInstancing>> m_GPUInstancings;
		std::unique_ptr<ImGuiPanel> m_ImguiPanel;
		std::unique_ptr<Camera> m_Camera;
		std::unordered_map<std::string, std::shared_ptr<Material>> m_Materials;
		glm::mat4 m_Projection, m_View;
	};
} // namespace FluidEngine
