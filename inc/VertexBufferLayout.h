#pragma once
#include <vector>
#include "Renderer.h"
#include <iostream>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;
    public:
        VertexBufferLayout()
            : m_Stride(0) {}

        template<typename T>
        inline void Push(unsigned int count)
        {
            static_assert(std::is_same<T, float>::value || std::is_same<T, unsigned int>::value, "Invalid type");
            std::cout << "Count: " << count << std::endl;
        }

        inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
        inline unsigned int GetStride() const { return m_Stride; }
};
