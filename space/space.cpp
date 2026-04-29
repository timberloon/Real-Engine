#include"nova/novapch.h"
#include"nova.h"


int main(){
    nova::log my_logger;
    my_logger.init();
    my_logger.log_to_client();

    if(!glfwInit()){
        my_logger.log_error("failed to init glfw\n");
        return 1;
    }

    auto wnd = glfwCreateWindow(1280,720,"Nova",NULL,NULL);
    glfwMakeContextCurrent(wnd);

    if(!glewInit()){
        my_logger.log_error("failed to init glew\n");
        return 1;
    }

    float points[] = {
        -0.5f, -0.5f,   0.0f,0.0f, // 0 
         0.5f, -0.5f,   1.0f,0.0f,// 1
         0.5f,  0.5f,   1.0f,1.0f,// 2
        -0.5f,  0.5f,   0.0f,1.0f// 3
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
    
    nova::IndexBuffer ibo(indices,18);

    std::string vert = "nova/src/renderer/shaders/vertex.glsl";
    std::string frag = "nova/src/renderer/shaders/fragment.glsl";   
    nova::shader shd(vert,frag);

    nova::texture TreeTexture("assets/summer_tree.png",false,GL_NEAREST,0);
    std::string texvert = "nova/src/renderer/shaders/texturevert.glsl";
    std::string texfrag = "nova/src/renderer/shaders/texturefrag.glsl"; 
    nova::shader TextureShader(texvert,texfrag);
    

    nova::renderer ren;

    while(!glfwWindowShouldClose(wnd)){
        glClear(GL_COLOR_BUFFER_BIT);
        
        // shd.addUniform4f("u_clr",0.43,0.77,0.66,1.0);
        // ren.draw(vao,ibo,shd);
        TextureShader.addUinform1i("myTexture",0);
        ren.draw(vao,ibo,TextureShader);

        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
    