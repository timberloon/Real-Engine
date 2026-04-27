#pragma once
#include"glcore.h"
#include<vector>

namespace nova{
    struct NOVA_API VertexBufferElement{
        uint type;
        uint count;
        u_char normalised;
    };

    class NOVA_API BufferLayout{
        uint m_stride;
        std::vector<VertexBufferElement> m_elements;
    public:
        BufferLayout() : m_stride(0){}

        template<typename t>
        void push(uint count);

        inline uint getStride(){return m_stride;}
        inline std::vector<VertexBufferElement> getElements(){return m_elements;}
    };
}