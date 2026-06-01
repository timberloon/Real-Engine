#pragma once
#include"glcore.h"
#include"vertexarray.h"
#include"indexbuffer.h"
#include"shader.h"
#include"Srect.h"
#include"texturerect.h"

namespace nova{
    class NOVA_API renderer{
    
    public:
        renderer() = default;
        ~renderer() = default;

        void draw(VertexArray& va,IndexBuffer& ib,shader& sh) const;
        void draw(Srect& rect) const;
        void draw(TextureRect& rect) const;
        inline void clear() const{glClear(GL_COLOR_BUFFER_BIT);}
    };
}