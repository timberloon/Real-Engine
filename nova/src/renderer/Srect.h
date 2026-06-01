#pragma once
#include"glcore.h"
#include"novaglobals.h"
#include"vertexarray.h"
#include"vertexbuffer.h"
#include"indexbuffer.h"
#include"shader.h"

namespace nova{
    class NOVA_API Srect{
        float m_points[8];
        uint m_indices[6];
        float m_width,m_height;
        nova::vec2 m_pos;

        nova::VertexArray m_vao;
        nova::VertexBuffer m_vbo;
        nova::BufferLayout m_layout;
        nova::IndexBuffer m_ibo;
     
        nova::shader m_shader;
    public:
        Srect(float x,float y,float w,float h);
        ~Srect(){}

        void bind();
        void unbind();
        void addColor(float r,float g,float b,float a);

        inline float getWidth(){return m_width;}
        inline float getHeight(){return m_height;}
        inline nova::vec2 getPos(){return m_pos;}
        inline float geXpos(){return m_pos.x;}
        inline float getYpos(){return m_pos.y;}

        inline nova::VertexArray& getVertexArray(){return m_vao;}
        inline nova::VertexBuffer& getVertexBuffer(){return m_vbo;}
        inline nova::IndexBuffer& getIndexBuffer(){return m_ibo;}
    };
}