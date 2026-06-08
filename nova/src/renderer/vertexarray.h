#pragma once
#include"glcore.h"
#include"vertexbuffer.h"
#include"bufferlayout.h"

namespace nova{
    class NOVA_API VertexArray{        
        uint m_vao;
    public:
        VertexArray();
        ~VertexArray();

        void addBuffer(VertexBuffer& vb,BufferLayout& lay);
        void addBuffer(VertexBuffer* vb,BufferLayout* lay);

        void bind();
        void unbind();
        inline uint getArrayId(){return m_vao;}
    };
}