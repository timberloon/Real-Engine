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

        auto clock = std::chrono::high_resolution_clock();
        auto temp = clock.now();
        std::chrono::_V2::system_clock::time_point buff;
        std::chrono::seconds interval(3);

        while(!myWindow.ShouldClose()){
            myWindow.clear();

            myScene.draw(player);
            buff = clock.now();
            if(buff-temp > interval)myScene.kill();

            myWindow.SwapBuffers();
            myWindow.PollEvents();
            myWindow.update();
        }
    }
}
