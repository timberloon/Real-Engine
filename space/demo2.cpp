#include"novapch.h"
#include"nova.h"

int main(){
    nova::log::init();
    nova::log::log_to_client();

    {
        nova::window myWindow(960,540,"MyWindow");

        nova::mat2 matr(1.0f,0.0f,0.0f,1.0f);
        nova::mat3 mat(1,2,3,4,5,6,7,8,9);
        nova::vec2 v(1.0,0.0);

        auto t = matr[0][0];
        auto u = mat[0][0];
        
        while(!myWindow.ShouldClose()){
            myWindow.clear();

            

            myWindow.SwapBuffers();
            myWindow.PollEvents();
            myWindow.update();
        }
    }
}
