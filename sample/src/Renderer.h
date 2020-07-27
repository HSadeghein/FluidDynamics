#pragma once
#include <iostream>
#include <unordered_map>
//#include "glad/glad.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderControler.h"
#include "BufferLayout.h"
#include "Texture.h"
#include "ImguiPanel.h"
#include "GameTimer.h"
#include "GeometryGenerator.h"
#include "Transform.h"
#include "Camera.h"
#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GL_CHECK_ERROR(x) GlClearErrors();\
x;\
ASSERT(GlDisplayError())

void GlClearErrors();
bool GlDisplayError();

namespace FluidEngine {
	class Renderer {
	public:
		Renderer(const std::vector<GeometryGenerator::Vertex> vertices, const std::vector<unsigned int> indices, Window* window);
		~Renderer();
		void Draw() const;
		void Clear() const;
		void Tick();
		void CalculateFrameStats();
		void RenderImgui(Window* window);
		void SetColor(const std::string& blockName, std::vector<float> color);
		void SetTexture(const char* path, const char* texName, int texSlot, bool invert);
		const std::vector<float> ConvertVerticesToArray(std::vector<GeometryGenerator::Vertex> vertices) const;
		void Blend(unsigned int src, unsigned int dest);
		void Model(const glm::vec3 translation, const glm::vec3 rotaion, const glm::vec3 scale);
		void SetCamera(CameraType cameraType);
		void SetCamera(CameraType cameraType, float fov, float aspect, float zNear, float zFar);
		void MVP(const std::string& blockName);

		inline glm::mat4& Projection() { return m_Projection; } 
		inline glm::mat4& Model()  { return m_Model; } 
		inline glm::mat4& View() { return m_View; } 

		std::unique_ptr<Camera> m_Camera;

	protected:
		float m_WindowHeight, m_WindowWidth;
		GameTimer m_Timer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<ShaderControler> m_Shader;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<BufferLayout> m_BufferLayout;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<ImGuiPanel> m_ImguiPanel;
		std::unique_ptr<Transform> m_Transform;
		std::unordered_map<std::string, glm::mat4> prevTransforms;
		glm::mat4 m_Projection, m_View, m_Model;
	};
}



