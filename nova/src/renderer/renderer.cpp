#include"renderer.h"

void nova::renderer::draw(VertexArray& va,IndexBuffer& ib,shader& sh) const{
    va.bind();
    ib.bind();
    sh.bind();
    glerr(glDrawElements(GL_TRIANGLES,ib.get_count(),GL_UNSIGNED_INT,nullptr));
}

void nova::renderer::draw(Srect& rect) const{
    rect.bind();
    glerr(glDrawElements(GL_TRIANGLES,rect.getIndexBuffer().get_count(),GL_UNSIGNED_INT,nullptr));
}

void nova::renderer::draw(TextureRect& rect) const{
    rect.bind();
    rect.m_shader.addUniform1i("myTexture",rect.getOffset());
    glerr(glDrawElements(GL_TRIANGLES,rect.getIndexBuffer().get_count(),GL_UNSIGNED_INT,nullptr));
}