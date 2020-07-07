#pragma once
#include "glad/glad.h"
#include<iostream>
#include "IndexBuffer.h"
#include "VertexArray.h"
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
		Renderer();
		void Draw(VertexArray& va, IndexBuffer& ib, ImGuiPanel& panel) const;
		void Clear() const;
		void Tick();
		void CalculateFrameStats();
	private:
		GameTimer m_Timer;
	};
}



