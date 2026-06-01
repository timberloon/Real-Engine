#include"nova/novapch.h"
#include"nova/nova.h"

int main(){
    nova::log::init();
    nova::log::log_to_client();

    nova::window mywindow(1280,720,"demo");
    { 
        // float bg[] = {
        //     -1.0f, 1.0f,     0.0f,0.0f, //0
        //     -1.0f,-1.0f,     0.0f,1.0f, //1
        //     1.0f,-1.0f,     1.0f,1.0f, //2
        //     1.0f, 1.0f,     1.0f,0.0f  //3
        // };
        float bg[] = {
            -1.0f/2, 1.0f/2,     0.0f,0.0f, //0
            -1.0f/2,-1.0f/2,     0.0f,1.0f, //1
            1.0f/2,-1.0f/2,     1.0f,1.0f, //2
            1.0f/2, 1.0f/2,     1.0f,0.0f  //3
        };

        uint indices[] = {
            0,1,2,
            0,2,3
        };

        nova::BufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);

        nova::VertexBuffer vbo(bg,sizeof(bg));

        nova::VertexArray vao;
        vao.addBuffer(vbo,layout);

        nova::IndexBuffer ibo(indices,6);


        std::string vert = "nova/src/renderer/shaders/vertex.glsl";
        std::string frag = "nova/src/renderer/shaders/fragment.glsl";   
        nova::shader PlainShader(vert,frag);

        nova::texture bgTexture("assets/hill_far.png",false,GL_NEAREST,0);
        std::string texvert = "nova/src/renderer/shaders/texturevert.glsl";
        std::string texfrag = "nova/src/renderer/shaders/texturefrag.glsl"; 
        nova::shader TextureShader(texvert,texfrag);

        nova::renderer paint;

        nova::texture fgTexture("assets/hill_near.png",false,GL_NEAREST,1);
        nova::texture skyTexture("assets/cloudy_sky1.png",false,GL_NEAREST,2);
        nova::texture treeTexture("assets/trees.png",false,GL_NEAREST,3);
        nova::texture cloud("assets/cloud.png",false,GL_NEAREST,4);

        while(!mywindow.ShouldClose()){
            glClear(GL_COLOR_BUFFER_BIT);

            // skyTexture.bind();
            // TextureShader.addUniform1i("myTexture",2);
            // paint.draw(vao,ibo,TextureShader);

            // fgTexture.bind();
            // TextureShader.addUniform1i("myTexture", 1);
            // paint.draw(vao, ibo, TextureShader);
                
            // bgTexture.bind();
            // TextureShader.addUniform1i("myTexture", 0); 
            // paint.draw(vao, ibo, TextureShader);

            // treeTexture.bind();
            // TextureShader.addUniform1i("myTexture",3);
            // paint.draw(vao,ibo,TextureShader);

            cloud.bind();
            TextureShader.addUniform1i("myTexture",4);
            paint.draw(vao,ibo,TextureShader);

            mywindow.SwapBuffers();
            mywindow.PollEvents();
            mywindow.update();
        }
    }

    return 0;
}