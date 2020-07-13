#pragma once
#include <iostream>
#include <unordered_map>
#include "glad/glad.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderControler.h"
#include "BufferLayout.h"
#include "Texture.h"
#include "ImguiPanel.h"
#include "GameTimer.h"
#include "GeometryGenerator.h"
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
		Renderer(const std::vector<GeometryGenerator::Vertex> vertices, const std::vector<unsigned int> indices, GLFWwindow* window);
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
		void OrthogonalProjection(const float& left, const float&right, const float& bottom, const float& top, const float& nearZ, const float& farZ);
		void Model(const glm::vec3 translation);
		void View(const glm::vec3 translation);
		void MVP(const std::string& blockName);

		inline glm::mat4& Projection() { return projection; } 
		inline glm::mat4& Model()  { return model; } 
		inline glm::mat4& View() { return view; } 

	protected:
		GameTimer m_Timer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<ShaderControler> m_Shader;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<BufferLayout> m_BufferLayout;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<ImGuiPanel> m_ImguiPanel;
		std::unordered_map<std::string, glm::mat4> prevTransforms;
		glm::mat4 projection, view, model;
	};
}



