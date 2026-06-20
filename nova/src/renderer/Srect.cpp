#include"Srect.h"

nova::Srect::Srect(float x,float y,float w,float h) : m_width(w), m_height(h){
    m_pos.a = x;m_pos.b = y;
    m_points[0] = x;   m_points[1] = y;
    m_points[2] = x+w; m_points[3] = y;
    m_points[4] = x+w; m_points[5] = y+h;
    m_points[6] = x;   m_points[7] = y+h;

    m_indices[0] = 0;m_indices[1] = 1;m_indices[2] = 3;
    m_indices[3] = 1;m_indices[4] = 2;m_indices[5] = 3;

    m_layout.push<float>(2);
    m_vbo.addData(m_points,sizeof(m_points));
    m_ibo.addData(m_indices,6);

    m_vao.addBuffer(m_vbo,m_layout);

    m_shader.define("nova/src/renderer/shaders/vertex.glsl","nova/src/renderer/shaders/fragment.glsl");
    m_shader.addUniform4f("u_clr",0.0f,0.0f,0.0f,0.0f);
    bind();
}

void nova::Srect::bind(){
    m_vao.bind();
    m_vbo.bind();
    m_ibo.bind();
    m_shader.bind();
}

void nova::Srect::addColor(float r,float g,float b,float a){
    m_shader.bind();
    m_shader.addUniform4f("u_clr",r,g,b,a);
}

void nova::Srect::unbind(){
    m_vao.unbind();
    m_vbo.unbind();
    m_ibo.unbind();
    m_shader.unbind();
}

void nova::Srect::updatePos(float x,float y){
    bind();
    this->m_pos.a = x;
    this->m_pos.b = y;

    m_points[0] = x;               m_points[1] = y;
    m_points[2] = x+this->m_width; m_points[3] = y;
    m_points[4] = x+this->m_width; m_points[5] = y+this->m_height;
    m_points[6] = x;               m_points[7] = y+this->m_height;

    m_vbo.addData(m_points,sizeof(m_points));
    m_vao.addBuffer(m_vbo,m_layout);
}