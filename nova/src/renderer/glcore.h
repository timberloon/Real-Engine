#pragma once

#include"core.h"
#include"../engine/log.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>

#define glerr(x) clearerror();\
    x;\
    assert(!geterrors(#x,__FILE__,__LINE__))

inline void clearerror(){
    while(glGetError() != GL_NO_ERROR);
}

static nova::log mylogger;

inline bool geterrors(const char* function, const char* file, uint line){
    while(auto error = glGetError()){
        std::stringstream strm;
        strm<< error << " in function: " << function << " in the file: " << file << " on line: " << line << '\n';
        mylogger.log_error(strm.str());
        return true;
    }
    return false;
}

inline uint getSizeOfType(uint type){
    switch(type){
        case GL_FLOAT: return 4;
        case GL_UNSIGNED_BYTE: return 1;
        case GL_UNSIGNED_INT: return 4;
    }
    return 0;
}