#include "VertexBuffer.h"
#include "Renderer.h"

namespace FluidEngine {
	VertexBuffer::VertexBuffer(const void* data, int size) 
	{
		GL_CHECK_ERROR(glGenBuffers(1, &m_RenderID));
		GL_CHECK_ERROR(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
		GL_CHECK_ERROR(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	VertexBuffer::~VertexBuffer()
	{
		GL_CHECK_ERROR(glDeleteBuffers(1, &m_RenderID));
	}

	void VertexBuffer::Bind()
	{
		GL_CHECK_ERROR(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
	}

	void VertexBuffer::Unbind()
	{
		GL_CHECK_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}