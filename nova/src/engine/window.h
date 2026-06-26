#pragma once
#include"core.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace nova{
    class NOVA_API window{
        GLFWwindow* m_window;
    public:
        float aspect;
        window(int width,int height,const char* title);
        ~window();
        
        bool ShouldClose();
        void SwapBuffers();
        void update();
        void PollEvents();
        void clear();
        void getFrameBufferSize(int* x,int* y);
        void ClearColor(float r,float g,float b,float a);

        inline GLFWwindow* getWindow(){return m_window;}
    };
}