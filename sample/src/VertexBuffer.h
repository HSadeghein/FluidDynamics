#pragma once

namespace FluidEngine {
	class VertexBuffer {
	public:
		VertexBuffer(const void* data, int size);
		~VertexBuffer();
		void Bind();
		void Unbind();
	private:
		unsigned int m_RenderID;
	};
}
