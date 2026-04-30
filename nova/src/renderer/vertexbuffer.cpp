#include"vertexbuffer.h"

nova::VertexBuffer::VertexBuffer(const void* data,unsigned int size){
    glerr(glGenBuffers(1,&buff));
    glBindBuffer(GL_ARRAY_BUFFER,buff);
    glerr(glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW));
}

nova::VertexBuffer::~VertexBuffer(){
    glerr(glDeleteBuffers(1,&buff));
}

void nova::VertexBuffer::bind(){
    glerr(glBindBuffer(GL_ARRAY_BUFFER,buff));
}

void nova::VertexBuffer::unbind(){
    glerr(glBindBuffer(GL_ARRAY_BUFFER,0));
}