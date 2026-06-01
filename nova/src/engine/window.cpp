#include"window.h"
#include"log.h"

nova::window::window(int width,int height,const char* title){
        if(!glfwInit()){
        nova::log::log_error("failed to init glfw\n");
        std::abort();
    }
    
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(width,height,title,nullptr,nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);


    if(!glewInit()){
        nova::log::log_error("failed to init glew\n");
        std::abort();
    }

    int fbW, fbH;
    glfwGetFramebufferSize(m_window, &fbW, &fbH);
    glViewport(0, 0, fbW, fbH);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

void nova::window::clear(){
    glClear(GL_COLOR_BUFFER_BIT);
}