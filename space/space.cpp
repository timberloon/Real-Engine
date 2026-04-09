#include"nova/src/novapch.h"
#include"nova.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#define sf(x) x*sizeof(float)
#define si(x) x*sizeof(int)

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

    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };

    GLuint buff;
    glGenBuffers(1,&buff);
    glBindBuffer(GL_ARRAY_BUFFER,buff);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sf(2),0);

    glBufferData(GL_ARRAY_BUFFER,6*sizeof(vertices),vertices,GL_STATIC_DRAW);

    while(!glfwWindowShouldClose(wnd)){
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES,0,3);

        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}