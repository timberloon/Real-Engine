#pragma once
#include"glcore.h"

namespace nova{
    class NOVA_API IndexBuffer{
        uint m_buff;
        uint m_count;
    public:
        IndexBuffer(const uint* data,uint count);
        IndexBuffer(){}
        ~IndexBuffer();

        void bind();
        void unbind();
        void addData(const uint* data,uint count);

        inline uint get_id(){return m_buff;}
        inline uint get_count(){return m_count;}
    };
}