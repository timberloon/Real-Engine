#include"bufferlayout.h"

template<>
void nova::BufferLayout::push<float>(uint count){
    m_elements.push_back({GL_FLOAT,count,GL_FALSE});
    m_stride += sizeof(GL_FLOAT) * count;
}

template<>
void nova::BufferLayout::push<uint>(uint count){
    m_elements.push_back({GL_UNSIGNED_INT,count,GL_FALSE});
    m_stride += sizeof(GL_UNSIGNED_INT) * count;
}

template<>
void nova::BufferLayout::push<u_char>(uint count){
    m_elements.push_back({GL_UNSIGNED_BYTE,count,GL_TRUE});
    m_stride += sizeof(GL_UNSIGNED_BYTE) * count;
}   