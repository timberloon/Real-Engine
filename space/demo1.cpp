#include"novapch.h"
#include"nova.h"

int main(){
    nova::log::init();
    nova::log::log_to_client();

    {
        nova::window myWindow(720,600,"MyWindow");

        nova::scene myScene;

        auto e = myScene.createEntity();
        myScene.addComponentToEntity(
            e,
            myScene.createComponent<nova::TransformComponent>(-0.5,0,0.5,0.5),
            myScene.createComponent<nova::SpriteComponent>("assets/cloud.png",true,GL_NEAREST,0)
        );
        
        auto f = myScene.createEntity();
        myScene.addComponentToEntity(
            f,
            myScene.createComponent<nova::TransformComponent>(-0.9,-0.5,0.5,0.5),
            myScene.createComponent<nova::SpriteComponent>("assets/summer_tree.png",true,GL_NEAREST,1)
        );

        while(!myWindow.ShouldClose()){
            myWindow.clear();

            myScene.draw(e);
            myScene.draw(f);

            myWindow.SwapBuffers();
            myWindow.PollEvents();
            myWindow.update();
        }
    }
}
