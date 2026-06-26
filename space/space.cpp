#include"nova/novapch.h"
#include"nova.h"

int main(){
    nova::log::init();
    nova::log::log_to_client();

    {   
        nova::window mywindow(960,540,"nova");
        
        while(!mywindow.ShouldClose()){
            mywindow.clear();

            mywindow.SwapBuffers();
            mywindow.PollEvents();
            mywindow.update();
        }
    }

    return 0;
}
