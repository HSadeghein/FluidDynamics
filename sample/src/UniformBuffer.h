#pragma once
namespace FluidEngine {
	class UniformBuffer {
	public:
		UniformBuffer();
		~UniformBuffer();

		void Bind(const float* data, int size, unsigned int binding);
		void Unbind(unsigned int binding);
	private:
		unsigned int m_RenderID;
	};
}