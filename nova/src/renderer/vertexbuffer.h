#pragma once
#include"glcore.h"

namespace nova{
    class NOVA_API VertexBuffer{
        uint buff;
    public:
        VertexBuffer(const void* data, unsigned int size);
        VertexBuffer(){}
        ~VertexBuffer();

        void bind();
        void unbind();
        void addData(const void* data,unsigned int size);

        inline uint get_id(){return buff;}
    };
}