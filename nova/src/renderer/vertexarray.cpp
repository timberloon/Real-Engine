#include"vertexarray.h"
#include<vector>

nova::VertexArray::VertexArray(){
    glerr(glGenVertexArrays(1,&m_vao));
    glerr(glBindVertexArray(m_vao));
}

nova::VertexArray::~VertexArray(){
    glerr(glDeleteVertexArrays(1,&m_vao));
}

void nova::VertexArray::bind(){
    glerr(glBindVertexArray(m_vao));
}

void nova::VertexArray::unbind(){
    glerr(glBindVertexArray(0));
}

void nova::VertexArray::addBuffer(nova::VertexBuffer& vb,nova::BufferLayout& lay){
    vb.bind();
    auto elements = lay.getElements();
    uint offset = 0;

    for(std::size_t i = 0;i<elements.size();i++){
        auto element = elements[i];
        glerr(glEnableVertexAttribArray(i));
        glerr(glVertexAttribPointer(
            i,
            element.count,
            element.type,
            element.normalised,
            lay.getStride(),
            (const void*)(uintptr_t) offset
        ));
        offset += element.count * getSizeOfType(element.type);
    }
}