#pragma once

#include"glcore.h"
#include"bufferlayout.h"
#include"indexbuffer.h"
#include"shader.h"
#include"texture.h"
#include"vertexarray.h"
#include"vertexbuffer.h"
#include"novaglobals.h"

namespace nova{
    class NOVA_API TextureRect{
        float m_points[16];
        uint m_indices[6];
        float m_width,m_height;
        nova::vec2 m_pos;
        int m_offset;

        nova::VertexArray m_vao;
        nova::VertexBuffer m_vbo;
        nova::BufferLayout m_layout;
        nova::IndexBuffer m_ibo;
     
        
    public:
        nova::texture m_texture;
        nova::shader m_shader;
       
        TextureRect(const char* path,float x,float y,float w,float h,bool flipped,int texture_filter,int texture_location);
        ~TextureRect(){}

        void bind();
        void unbind();

        inline float getWidth(){return m_width;}
        inline float getHeight(){return m_height;}
        inline nova::vec2 getPos(){return m_pos;}
        inline float geXpos(){return m_pos.x;}
        inline float getYpos(){return m_pos.y;}
        inline int getOffset(){return m_offset;}

        inline nova::VertexArray& getVertexArray(){return m_vao;}
        inline nova::VertexBuffer& getVertexBuffer(){return m_vbo;}
        inline nova::IndexBuffer& getIndexBuffer(){return m_ibo;}
    };
}