#include"novapch.h"
#include"nova.h"

int main(){
    nova::log::init();
    nova::log::log_to_client();

    {
        nova::window myWindow(720,600,"MyWindow");

        IMGUI_CHECKVERSION();
        auto t = ImGui::CreateContext();
        if(!t) nova::log::log_error("Failed to Create ImGui Context!\n");
        
        while(!myWindow.ShouldClose()){
            myWindow.clear();

            

            myWindow.SwapBuffers();
            myWindow.PollEvents();
            myWindow.update();
        }
    }
}
