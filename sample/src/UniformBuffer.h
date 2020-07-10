#pragma once
namespace FluidEngine {
	class UniformBuffer {
	public:
		UniformBuffer(const void* data, int size);
		~UniformBuffer();

		void Bind();
		void Unbind();
	private:
		unsigned int m_RenderID;
	};
}