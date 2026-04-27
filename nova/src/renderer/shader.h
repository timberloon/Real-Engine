#pragma once
#include"glcore.h"

namespace nova{

    static nova::log mylogger;

    class NOVA_API shader{
        uint m_VertexShader;
        uint m_FragmentShader;

        uint m_program;

        inline std::string openshader(const std::string& path){
            std::ifstream file(path);

            if(!file.is_open()){
                mylogger.log_error("could not open file");
                assert(1);
            }

            std::stringstream buffer;

            buffer << file.rdbuf();
            return buffer.str();
        }

    public:
        shader(const std::string& vertpath,const std::string& fragpath);
        ~shader();

        inline void bind() const{glerr(glUseProgram(m_program));}
        inline void unbind() const{glerr(glUseProgram(0));}

        void addUniform4f(const char* attrib,float a,float b,float c,float d);
        
        inline uint getVertexShader(){return m_VertexShader;}
        inline uint getFragmentShader(){return m_FragmentShader;}
        inline uint getProgram(){return m_program;}
    };
}