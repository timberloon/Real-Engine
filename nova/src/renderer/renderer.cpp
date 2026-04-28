#include"renderer.h"

void nova::renderer::draw(VertexArray& va,IndexBuffer& ib,shader& sh) const{
    va.bind();
    ib.bind();
    sh.bind();
    glerr(glDrawElements(GL_TRIANGLES,ib.get_count(),GL_UNSIGNED_INT,nullptr));
}