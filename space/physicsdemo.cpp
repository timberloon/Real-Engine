#include<novapch.h>
#include<nova.h>

int main(){
    nova::log::init();
    nova::log::log_to_client();
    {
        nova::window myWindow(960,540,"Physics World");

        nova::scene myScene;
        auto player = myScene.createEntity();
        myScene.addComponentToEntity(
            player,
            myScene.createComponent<nova::TransformComponent>(0,4,2,2),
            myScene.createComponent<nova::SpriteComponent>("assets/player.png",true,GL_NEAREST,0),
            myScene.createComponent<nova::VelocityComponent>(0,0),
            myScene.createComponent<nova::AccelarationComponent>(0,0),
            myScene.createComponent<nova::MassComponent>(20),
            myScene.createComponent<nova::ForceComponent>(0.001,0.0)
        );

        double frameStartTime = NOVA_GET_TIME;

        while(!myWindow.ShouldClose()){
            double currTime = NOVA_GET_TIME;
            double FrameTime = currTime-frameStartTime;            
            frameStartTime = currTime;
             
            myScene.draw(player);
            myScene.update(player,FrameTime);
            
            myWindow.SwapBuffers();
            myWindow.PollEvents();
            myWindow.update();

            myWindow.clear();
        }
    }
}