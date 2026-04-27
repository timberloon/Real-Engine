#include"indexbuffer.h"

nova::IndexBuffer::IndexBuffer(const uint* data,uint count) : m_count(count){
    glerr(glGenBuffers(1,&m_buff));
    glerr(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_buff));
    glerr(glBufferData(GL_ELEMENT_ARRAY_BUFFER,sui(m_count),data,GL_STATIC_DRAW));
}

nova::IndexBuffer::~IndexBuffer(){
    glerr(glDeleteBuffers(1,&m_buff));
}

void nova::IndexBuffer::bind(){
    glerr(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_buff));
}

void nova::IndexBuffer::unbind(){
    glerr(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}