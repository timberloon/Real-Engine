#include"nova/novapch.h"
#include"nova.h"

int main(){
    nova::log::init();
    nova::log::log_to_client();

    {   
        nova::window mywindow(950,630,"nova");

        nova::TextureRect sky("assets/cloudy_sky1.png",-1,-1,2,2,true,GL_NEAREST,0);
        nova::TextureRect cloud("assets/cloud.png",0,0,1,0.7,true,GL_NEAREST,1);
        nova::TextureRect hillfar("assets/hill_far.png",-1,-1,2,2,true,GL_NEAREST,2);
        nova::TextureRect hillnear("assets/hill_near.png",-1,-1,2,2,true,GL_NEAREST,3);
        nova::TextureRect trees("assets/trees.png",-1,-1,2,2,true,GL_NEAREST,4);

        nova::Srect rect(-1,0,0.5,0.5);
        rect.addColor(0.2,0.5,0.3,1.0);
        
        nova::renderer ren;
        
        while(!mywindow.ShouldClose()){
            mywindow.clear();
            
            cloud.updatePos(cloud.getXpos()+0.0005,cloud.getYpos()+0.0005); 

            ren.draw(sky);
            ren.draw(cloud);
            ren.draw(hillfar);
            ren.draw(hillnear);
            ren.draw(trees);
            
            mywindow.SwapBuffers();
            mywindow.PollEvents();
            mywindow.update();
        }
    }

    return 0;
}
