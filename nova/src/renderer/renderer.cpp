#include"renderer.h"

void nova::renderer::draw(VertexArray& va,IndexBuffer& ib,shader& sh) const{
    va.bind();
    ib.bind();
    sh.bind();
    glerr(glDrawElements(GL_TRIANGLES,18,GL_UNSIGNED_INT,nullptr));
}