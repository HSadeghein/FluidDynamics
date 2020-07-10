#include "pch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include<iostream>

namespace FluidEngine {
	VertexArray::VertexArray()
	{
		GL_CHECK_ERROR(glGenVertexArrays(1, &m_RenderID));
		GL_CHECK_ERROR(glBindVertexArray(m_RenderID));
	}

	VertexArray::~VertexArray()
	{
		GL_CHECK_ERROR(glDeleteVertexArrays(1, &m_RenderID));
		std::cout << "Vertex Array is destroyed" << std::endl;
	}

	void VertexArray::Bind()
	{
		GL_CHECK_ERROR(glBindVertexArray(m_RenderID));
	}

	void VertexArray::Unbind()
	{
		GL_CHECK_ERROR(glBindVertexArray(0));
	}

	void VertexArray::AddBuffer(BufferLayout& bufferLayout, VertexBuffer& vertexBuffer)
	{
		vertexBuffer.Bind();
		std::vector<BufferElement> elements = bufferLayout.GetElements();
		unsigned int offset = 0;
		for (int i=0;i< elements.size(); i++)
		{
			BufferElement element = elements[i];
			GL_CHECK_ERROR(glEnableVertexAttribArray(i));
			GL_CHECK_ERROR(glVertexAttribPointer(i, element.count, element.type, element.normalized,
				bufferLayout.GetStride(), (const void*)offset));
			offset += element.count * sizeof(element.type);
		}
	}
}