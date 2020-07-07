#include "IndexBuffer.h"
#include "Renderer.h"

namespace FluidEngine {
	IndexBuffer::IndexBuffer(const unsigned int* data, int count) : m_Count(count)
	{
		GL_CHECK_ERROR(glGenBuffers(1, &m_RenderID));
		GL_CHECK_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
		GL_CHECK_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		GL_CHECK_ERROR(glDeleteBuffers(1, &m_RenderID));
	}

	void IndexBuffer::Bind()
	{
		GL_CHECK_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
	}

	void IndexBuffer::Unbind()
	{
		GL_CHECK_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}