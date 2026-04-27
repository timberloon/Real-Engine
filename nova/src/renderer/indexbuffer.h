#pragma once
#include"glcore.h"

namespace nova{
    class NOVA_API IndexBuffer{
        uint m_buff;
        uint m_count;
    public:
        IndexBuffer(const uint* data,uint count);
        ~IndexBuffer();

        void bind();
        void unbind();

        inline uint get_id(){return m_buff;}
    };
}