#pragma once
#include <vector>
#include<glad/glad.h>

namespace FluidEngine {

    struct BufferElement {
        unsigned int count;
        unsigned int type;
        bool normalized;
    };

    class BufferLayout {
    public:
        BufferLayout() : m_Stride(0) {}

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

        inline const unsigned int GetStride() const{ return m_Stride; }
        inline const std::vector<BufferElement> GetElements() const { return m_Elements; }

    private:
        std::vector<BufferElement> m_Elements;
        unsigned int m_Stride;
    };
}