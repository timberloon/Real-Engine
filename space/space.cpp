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

    auto wnd = glfwCreateWindow(800,600,"Nova",NULL,NULL);
    glfwMakeContextCurrent(wnd);

    if(!glewInit()){
        my_logger.log_error("failed to init glew\n");
        return 1;
    }

    float points[] = {
        0.0f,0.0f,
        0.5f,0.0f,
        0.25f,0.43f,
        -0.25f,0.43f,
        -0.5f,0.0f,
        -0.25f,-0.43f,
        0.25f,-0.43f
    };

    uint indices[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,1
    };

    nova::BufferLayout layout;
    layout.push<float>(2);

    nova::VertexBuffer vbo(points,sizeof(points));
    
    nova::VertexArray vao;
    vao.addBuffer(vbo,layout);
    
    nova::IndexBuffer ibo(indices,18);

    std::string vert = "nova/src/renderer/shaders/vertex.glsl";
    std::string frag = "nova/src/renderer/shaders/fragment.glsl";   
    nova::shader shd(vert,frag);

    nova::renderer ren;

    while(!glfwWindowShouldClose(wnd)){
        glClear(GL_COLOR_BUFFER_BIT);
        
        shd.addUniform4f("u_clr",0.43,0.77,0.66,1.0);
        ren.draw(vao,ibo,shd);

        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
