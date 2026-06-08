#include"novapch.h"
#include"nova.h"

int main(){
    nova::log::init();
    nova::log::log_to_client();

    {
        nova::window myWindow(950,630,"MyWindow");

        nova::scene myScene;
        entity player = myScene.createEntity();

        auto playerPos = myScene.createComponent<nova::TransformComponent>(-0.5f,-0.5f,1.0f,1.0f);
        auto playerBlock = myScene.createComponent<nova::ColorComponent>(0.43,0.67,0.21,1.0);
        auto playerSprite = myScene.createComponent<nova::SpriteComponent>("assets/cloud.png",-0.5f,-0.5f,1.0f,1.0f,true,GL_NEAREST,0);

        myScene.addComponentToEntity(player,playerPos,playerSprite);

        while(!myWindow.ShouldClose()){
            myWindow.clear();

            myScene.draw(player);

            myWindow.SwapBuffers();
            myWindow.PollEvents();
            myWindow.update();
        }
    }
}