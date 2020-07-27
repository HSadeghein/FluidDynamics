#pragma once
#include "GeometryGenerator.h"
#include "glm/glm.hpp"

namespace FluidEngine {
	class VertexBuffer {
	public:
		VertexBuffer();
		VertexBuffer(const void* data, int size, unsigned int drawType);
		~VertexBuffer();
		void Bind();
		void Unbind();
		void BufferSubData(int size, const GeometryGenerator::Vertex* data);
		void BufferData(int size, const glm::mat4* data, unsigned int drawType);
		void BufferData(int size, const GeometryGenerator::Vertex* data, int drawType);
	private:
		unsigned int m_RenderID;
	};
}
