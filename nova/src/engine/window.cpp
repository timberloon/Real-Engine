#include"window.h"
#include"log.h"

nova::window::window(int width,int height,const char* title){
        if(!glfwInit()){
        nova::log::log_error("failed to init glfw\n");
        std::abort();
    }

    m_window = glfwCreateWindow(width,height,title,nullptr,nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    if(!glewInit()){
        nova::log::log_error("failed to init glew\n");
        std::abort();
    }
}

nova::window::~window(){
    glfwTerminate();
}

bool nova::window::ShouldClose(){
    return glfwWindowShouldClose(m_window);
}

void nova::window::SwapBuffers(){
    glfwSwapBuffers(m_window);
}

void nova::window::update(){

}

void nova::window::PollEvents(){
    glfwPollEvents();
}