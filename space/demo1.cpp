#include"novapch.h"
#include"nova.h"

int main(){
    nova::log::init();
    nova::log::log_to_client();

    {
        nova::window myWindow(960,540,"MyWindow");

        nova::scene myScene(myWindow.aspect);

        auto e = myScene.createEntity();
        myScene.addComponentToEntity(
            e,
            myScene.createComponent<nova::TransformComponent>(8,4,2,2),
            myScene.createComponent<nova::SpriteComponent>("assets/cloudy_sky1.png",true,GL_NEAREST,0)
        );
        
        auto f = myScene.createEntity();
        myScene.addComponentToEntity(
            f,
            myScene.createComponent<nova::TransformComponent>(8,4,2,2),
            myScene.createComponent<nova::SpriteComponent>("assets/cloudy_sky1.png",true,GL_NEAREST,1)
        );

        auto time = std::chrono::high_resolution_clock();
        auto curr = time.now();
        std::chrono::seconds interval(2);
        bool flag = false;

        uint CurrDistance = 0;
        while(!myWindow.ShouldClose()){
            myWindow.clear();

            // myScene.draw(f);
            myScene.draw(e);
            if(!flag && time.now() - curr > interval){
                myScene.TranslateEntity(e,2,0);
                myScene.ScaleEntity(e,2,2);
                myScene.RotateEntity(e,M_PI/4);
                flag = true;
            }
            myWindow.SwapBuffers();
            myWindow.PollEvents();
            myWindow.update();
        }
    }
}

