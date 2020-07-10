#pragma once
#include "glad/glad.h"
#include<iostream>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderControler.h"
#include "BufferLayout.h"
#include "Texture.h"
#include "ImguiPanel.h"
#include "GameTimer.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GL_CHECK_ERROR(x) GlClearErrors();\
x;\
ASSERT(GlDisplayError())

void GlClearErrors();
bool GlDisplayError();

namespace FluidEngine {
	class Renderer {
	public:
		Renderer(const std::vector<float> vertices, const std::vector<unsigned int> indices);
		~Renderer();
		void Draw(ImGuiPanel& panel) const;
		void Clear() const;
		void Tick();
		void CalculateFrameStats();
		void SetColor(const std::string& blockName, std::vector<float> color);
		void SetTexture(const char* path, const char* texName, int texSlot);
	protected:
		GameTimer m_Timer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<ShaderControler> m_Shader;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<BufferLayout> m_BufferLayout;
		std::unique_ptr<Texture> m_Texture;
	};
}



