#include"scene.h"
#include"physics/physics2D.h"

nova::scene::scene(){
    this->m_alive = true;
    m_solidShader.define("nova/src/renderer/shaders/vertex.glsl","nova/src/renderer/shaders/fragment.glsl");
    m_textureShader.define("nova/src/renderer/shaders/texturevert.glsl","nova/src/renderer/shaders/texturefrag.glsl");

    nova::mat4 matrix = nova::ortho(0,16,0,9,0,1.0);
    m_solidShader.addUniformMat4("projection",matrix);
    m_textureShader.addUniformMat4("projection",matrix);

    m_layout = nullptr;
    m_vao = nullptr;
    m_vbo = nullptr;
    m_ibo = nullptr;
}

void nova::scene::draw(entity& e){
    if(!m_alive) return;
    auto transform = m_registry.getComponent<TransformComponent>(e);
    auto sprite = m_registry.getComponent<SpriteComponent>(e);
    auto color = m_registry.getComponent<ColorComponent>(e);

    if(m_layout) delete m_layout;
    if(m_vao) delete m_vao;
    if(m_vbo) delete m_vbo;
    if(m_ibo) delete m_ibo;

    if(!transform) return;
    if(sprite){
        float points[16];
        points[0] =  transform->m_points[0];  points[1] =  transform->m_points[1];  points[2] = 0.0f;  points[3] = 0.0f;
        points[4] =  transform->m_points[2];  points[5] =  transform->m_points[3];  points[6] = 1.0f;  points[7] = 0.0f;
        points[8] =  transform->m_points[4];  points[9] =  transform->m_points[5];  points[10] = 1.0f; points[11] = 1.0f;
        points[12] = transform->m_points[6];  points[13] = transform->m_points[7];  points[14] = 0.0f; points[15] = 1.0f;

        m_layout = new nova::BufferLayout();
        m_layout->push<float>(2);
        m_layout->push<float>(2);
        m_vbo = new nova::VertexBuffer(points,sizeof(points));
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

void nova::scene::update(entity& e,float delta){
    auto mass = m_registry.getComponent<MassComponent>(e);
    auto force = m_registry.getComponent<ForceComponent>(e);
    auto acc = m_registry.getComponent<AccelarationComponent>(e);
    auto velocity = m_registry.getComponent<VelocityComponent>(e);    

    nova::mat3 transform;

    if(mass && force) transform = nova::physics::CalculateTransform(delta,*velocity,*acc,*force,*mass); 
    else if(acc) transform = nova::physics::CalculateTransform(delta,*velocity,*acc);
    else if(velocity) transform = nova::physics::CalculateTransform(delta,*velocity);
    m_registry.TransformEntity(e,transform);
}