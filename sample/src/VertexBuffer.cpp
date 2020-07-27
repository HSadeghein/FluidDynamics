#include "pch.h"
#include "VertexBuffer.h"
#include "Renderer.h"
#include <iostream>

namespace FluidEngine {
	VertexBuffer::VertexBuffer()
	{
		GL_CHECK_ERROR(glGenBuffers(1, &m_RenderID));
		GL_CHECK_ERROR(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
	}

	VertexBuffer::VertexBuffer(const void* data, int size, unsigned int drawType)
	{
		GL_CHECK_ERROR(glGenBuffers(1, &m_RenderID));
		GL_CHECK_ERROR(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
		GL_CHECK_ERROR(glBufferData(GL_ARRAY_BUFFER, size, data, drawType));
	}

	VertexBuffer::~VertexBuffer()
	{
		std::cout << "Vertex buffer is destroyed" << std::endl;
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

	void VertexBuffer::BufferSubData(int size, const GeometryGenerator::Vertex* data)
	{
		GL_CHECK_ERROR(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
	}

	void VertexBuffer::BufferData(int size, const GeometryGenerator::Vertex* data, int drawType)
	{
		GL_CHECK_ERROR(glBufferData(GL_ARRAY_BUFFER, size, data, drawType));
	}

	void VertexBuffer::BufferData(int size, const glm::mat4* data, unsigned int drawType)
	{
		GL_CHECK_ERROR(glBufferData(GL_ARRAY_BUFFER, size, data, drawType));
	}
}