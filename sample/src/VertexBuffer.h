#pragma once
#include "GeometryGenerator.h"

namespace FluidEngine {
	class VertexBuffer {
	public:
		VertexBuffer(const float* data, int size);
		~VertexBuffer();
		void Bind();
		void Unbind();
	private:
		unsigned int m_RenderID;
	};
}
