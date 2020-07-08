#pragma once
namespace FluidEngine {
	class IndexBuffer {
	public:
		IndexBuffer(const unsigned int* data, int count);
		~IndexBuffer();
		void Bind();
		void Unbind();
		inline const int GetCount() const { return m_Count;  }
	private:
		unsigned int m_RenderID;
		int m_Count;
	};
}