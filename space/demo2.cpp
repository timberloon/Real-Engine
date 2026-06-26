#include"novapch.h"
#include"nova.h"

int main(){
    nova::log::init();
    nova::log::log_to_client();

    {
        nova::window myWindow(960,540,"MyWindow");

        
        
        while(!myWindow.ShouldClose()){
            myWindow.clear();

            

            myWindow.SwapBuffers();
            myWindow.PollEvents();
            myWindow.update();
        }
    }
}
