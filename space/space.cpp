#include"nova/novapch.h"
#include"nova.h"


int main(){
    nova::log::init();
    nova::log::log_to_client();

    nova::window mywindow(1280,720,"nova");

    {   
        float points[] = {
            -0.5f, -0.5f,   0.0f,0.0f,  // 0 
            0.5f, -0.5f,   1.0f,0.0f,  // 1
            0.5f,  0.5f,   1.0f,1.0f,  // 2
            -0.5f,  0.5f,   0.0f,1.0f   // 3
        };

        uint indices[] = {
            0,1,3,
            1,2,3
        };

        nova::BufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);

        nova::VertexBuffer vbo(points,sizeof(points));
        
        nova::VertexArray vao;
        vao.addBuffer(vbo,layout);
        
        nova::IndexBuffer ibo(indices,6);

        std::string vert = "nova/src/renderer/shaders/vertex.glsl";
        std::string frag = "nova/src/renderer/shaders/fragment.glsl";   
        nova::shader PlainShader(vert,frag);

        nova::texture TreeTexture("assets/summer_tree.png",false,GL_NEAREST,0);
        std::string texvert = "nova/src/renderer/shaders/texturevert.glsl";
        std::string texfrag = "nova/src/renderer/shaders/texturefrag.glsl"; 
        nova::shader TextureShader(texvert,texfrag);
        

        nova::renderer ren;

        while(!mywindow.ShouldClose()){
            glClear(GL_COLOR_BUFFER_BIT);
            
            TextureShader.addUniform1i("myTexture",0);
            ren.draw(vao,ibo,TextureShader);

            mywindow.SwapBuffers();
            mywindow.PollEvents();
            mywindow.update();
        }
    }

    return 0;
}
    