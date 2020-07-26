#pragma once
#include <vector>
#include<iostream>

#define GL_FLOAT 0x1406
#define GL_UNSIGNED_INT 0x1405
#define GL_UNSIGNED_BYTE 0x1401
#define GL_FALSE 0
#define GL_TRUE 1

namespace FluidEngine {

    struct BufferElement {
        unsigned int count;
        unsigned int type;
        bool normalized;
    };

    class BufferLayout {
    public:
        BufferLayout() : m_Stride(0) {}
        ~BufferLayout() { std::cout << "Renderer is destroyed" << std::endl; }

        template<typename T>
        void Push(unsigned int count)
        {
            static_assert(false);
        }

        template<>
        void Push<float>(unsigned int count)
        {
            m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
            m_Stride += count * sizeof(float);
        }

        template<>
        void Push<unsigned int>(unsigned int count)
        {
            m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
            m_Stride += count * sizeof(unsigned int);
        }

        template<>
        void Push<unsigned char>(unsigned int count)
        {
            m_Elements.push_back( {count, GL_UNSIGNED_BYTE, GL_TRUE} );
            m_Stride += count * sizeof(unsigned char);
        }

        void Clear()
        {
            m_Elements.clear();
            m_Stride = 0;
        }

        inline const unsigned int GetStride() const{ return m_Stride; }
        inline const std::vector<BufferElement> GetElements() const { return m_Elements; }

    private:
        std::vector<BufferElement> m_Elements;
        unsigned int m_Stride;
    };
}