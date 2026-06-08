#include"scene.h"

nova::scene::scene(){
    m_solidShader.define("nova/src/renderer/shaders/vertex.glsl","nova/src/renderer/shaders/fragment.glsl");
    m_textureShader.define("nova/src/renderer/shaders/texturevert.glsl","nova/src/renderer/shaders/texturefrag.glsl");

    m_layout = nullptr;
    m_vao = nullptr;
    m_vbo = nullptr;
    m_ibo = nullptr;
}

void nova::scene::draw(entity& e){
    auto transform = m_registry.getComponent<TransformComponent>(e);
    auto sprite = m_registry.getComponent<SpriteComponent>(e);
    auto color = m_registry.getComponent<ColorComponent>(e);

    if(m_layout) delete m_layout;
    if(m_vao) delete m_vao;
    if(m_vbo) delete m_vbo;
    if(m_ibo) delete m_ibo;

    if(!transform) return;
    if(sprite){
        m_layout = new nova::BufferLayout();
        m_layout->push<float>(2);
        m_layout->push<float>(2);
        m_vbo = new nova::VertexBuffer(sprite->m_points,sizeof(sprite->m_points));
        m_vao = new nova::VertexArray;
        m_vao->addBuffer(m_vbo,m_layout);
        m_ibo = new nova::IndexBuffer(transform->m_indices,6);

        m_textureShader.bind();
        m_textureShader.addUniform1i("myTexture",sprite->m_texture_location_offset);

        nova::texture temptex(sprite->m_texturePath,sprite->m_flipped,sprite->m_textureFilter,sprite->m_texture_location_offset);
        temptex.bind();

        m_renderer.draw(*m_vao,*m_ibo,m_textureShader);
    }
    else if(color){
        m_layout = new nova::BufferLayout();
        m_layout->push<float>(2);
        m_vbo = new nova::VertexBuffer(transform->m_points,sizeof(transform->m_points));
        m_vao = new nova::VertexArray;
        m_vao->addBuffer(m_vbo,m_layout);
        m_ibo = new nova::IndexBuffer(transform->m_indices,6);

        m_solidShader.bind();
        m_solidShader.addUniform4f("u_clr",color->r,color->g,color->b,color->a);

        m_renderer.draw(*m_vao,*m_ibo,m_solidShader);
    }
    else{
        nova::log::log_error("both color and sprite are null!\n");
    }
}
