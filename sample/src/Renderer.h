#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderControler.h"
#include "BufferLayout.h"
#include "Texture.h"
#include "ImguiPanel.h"
#include "GameTimer.h"
#include "Camera.h"
#include "Object.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"

#define VERTEX_ATTRIB_VB 0
#define WVP_MATRIX_VB 1
#define WORLD_MATRIX_VB 2

#define ASSERT(x) if(!(x)) __debugbreak();
#define GL_CHECK_ERROR(x) GlClearErrors();\
x;\
ASSERT(GlDisplayError())

void GlClearErrors();
bool GlDisplayError();

namespace FluidEngine {
	class Renderer {
	public:
		Renderer(Window* window);
		~Renderer();
		void InstanceDraw() const;
		void Clear() const;
		void Tick();
		void CalculateFrameStats();
		void RenderImgui(Window* window);
		Material* CreateMaterial(std::string vertexShader, std::string pixelShader, std::string texturePath, glm::vec4 color);
		void SetCamera(CameraType cameraType);
		void SetCamera(CameraType cameraType, float fov, float aspect, float zNear, float zFar);
		void InstertObject(Object* object);
		void SetUpGPUInstancing(Mesh* mesh, int instanceNumber);
		void SetUpInstancingBuffers(Mesh* mesh);
		void InstantiateInstanceTransforms(int instanceNumber);
		void UpdateTransforms();
		inline glm::mat4& Projection() { return m_Projection; } 
		inline glm::mat4& View() { return m_View; } 

	protected:
		int m_InstanceNumber;
		int m_WindowHeight, m_WindowWidth;
		GameTimer m_Timer;
		std::unique_ptr<VertexBuffer> m_VertexBuffers[3];
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<BufferLayout> m_BufferLayout;
		std::unique_ptr<ImGuiPanel> m_ImguiPanel;
		std::unique_ptr<Camera> m_Camera;
		std::vector<std::unique_ptr<Material>> m_Materials;
		std::vector<Object*> m_Objects;
		std::vector<glm::mat4> m_WVPs;
		std::vector<glm::mat4> m_Worlds;
		glm::mat4 m_Projection, m_View;
	};
}



