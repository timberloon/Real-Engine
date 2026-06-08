#include"texturerect.h"

nova::TextureRect::TextureRect(const char* path,float x,float y,float w,float h,bool flipped,int texture_filter,int texture_location_offset): \
    m_texture_location_offset(texture_location_offset),m_width(w), m_height(h), m_pos(x,y), m_texture(path,flipped,texture_filter,texture_location_offset){
        m_points[0] = x;   m_points[1] = y;    m_points[2] = 0.0f;  m_points[3] = 0.0f;
        m_points[4] = x+w; m_points[5] = y;    m_points[6] = 1.0f;  m_points[7] = 0.0f;
        m_points[8] = x+w; m_points[9] = y+h;  m_points[10] = 1.0f; m_points[11] = 1.0f;
        m_points[12] = x;  m_points[13] = y+h; m_points[14] = 0.0f; m_points[15] = 1.0f;

        m_indices[0] = 0;m_indices[1] = 1;m_indices[2] = 3;
        m_indices[3] = 1;m_indices[4] = 2;m_indices[5] = 3;

        m_layout.push<float>(2);
        m_layout.push<float>(2);

        m_vbo.addData(m_points,sizeof(m_points));
        m_vao.addBuffer(m_vbo,m_layout);
        m_ibo.addData(m_indices,6);

        m_shader.define("nova/src/renderer/shaders/texturevert.glsl","nova/src/renderer/shaders/texturefrag.glsl");
        bind();
    }

void nova::TextureRect::bind(){
    m_vao.bind();
    m_vbo.bind();
    m_ibo.bind();
    m_shader.bind();
    m_texture.bind();
}

void nova::TextureRect::unbind(){
    m_ibo.unbind();
    m_vao.unbind();
    m_vbo.unbind();
    m_shader.unbind();
    m_texture.unbind();
}

void nova::TextureRect::updatePos(float x,float y){
    bind();
    this->m_pos.x = x;
    this->m_pos.y = y;

    m_points[0] = x;                m_points[1] = y;                 
    m_points[4] = x+this->m_width ; m_points[5] = y;                 
    m_points[8] = x+this->m_width ; m_points[9] = y+this->m_height ; 
    m_points[12] = x;               m_points[13] = y+this->m_height ;

    m_vbo.addData(m_points,sizeof(m_points));
    m_vao.addBuffer(m_vbo,m_layout);
}