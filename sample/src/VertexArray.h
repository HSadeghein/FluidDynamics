#pragma once
#include "BufferLayout.h"
#include "VertexBuffer.h"

namespace FluidEngine {

    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();
        void Bind();
        void Unbind();
        void AddBuffer(BufferLayout& bufferLayout, VertexBuffer& vertexBuffer);
    private:
        unsigned int m_RenderID;
    };
}