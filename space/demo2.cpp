#include"novapch.h"
#include"nova.h"

int main(){
    nova::log::init();
    nova::log::log_to_client();

    {
        nova::window myWindow(720,600,"MyWindow");

        nova::scene myScene;
        auto pos = myScene.createComponent<nova::TransformComponent>(-0.5,0,0.5,0.5);
        auto clr = myScene.createComponent<nova::ColorComponent>(0.43,0.67,0.21,1.0);
        auto sprite = myScene.createComponent<nova::SpriteComponent>("assets/cloud.png",-0.5f,-0.5f,1.0f,1.0f,true,GL_NEAREST,0);

        auto e = myScene.createEntity();
        myScene.addComponentToEntity(e,pos,sprite);

        // nova::BufferLayout layout;
        // layout.push<float>(2);
        // layout.push<float>(2);
        // nova::VertexBuffer vbo(sprite->m_points,sizeof(sprite->m_points));
        // nova::VertexArray vao;
        // vao.addBuffer(vbo,layout);
        // nova::IndexBuffer ibo(pos->m_indices,6);

        // nova::shader texShader("nova/src/renderer/shaders/texturevert.glsl","nova/src/renderer/shaders/texturefrag.glsl");
        // texShader.bind();

        // nova::texture cloudTexture(sprite->m_texturePath,sprite->m_flipped,sprite->m_textureFilter,sprite->m_texture_location_offset);
        // cloudTexture.bind();

        nova::renderer ren;

        while(!myWindow.ShouldClose()){
            myWindow.clear();

            myScene.draw(e);
            // ren.draw(vao,ibo,texShader);

            myWindow.SwapBuffers();
            myWindow.PollEvents();
            myWindow.update();
        }
    }
}