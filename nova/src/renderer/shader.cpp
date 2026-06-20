#include"shader.h"

template<typename t>
static void linkshaders(const uint& program,const t& shader){
    glerr(glAttachShader(program,shader));

    glerr(glDeleteShader(shader));
}

template<typename t,typename... targs>
static void linkshaders(const uint& program,const t& shader,const targs&...args){
    glerr(glAttachShader(program,shader));
    linkshaders(program,args...);
}

static void compileCheck(const uint& shader){
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success){
        char info[512];
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::stringstream s;
        s << "VERTEX SHADER ERROR:\n" << info << std::endl;
        nova::log::log_error(s.str());
        std::abort();
    }
}

static void linkCheck(const uint& program){
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success){
        char info[512];
        glGetProgramInfoLog(program, 512, nullptr, info);
        std::stringstream s;
        s << "PROGRAM LINK ERROR:\n" << info << std::endl;
        nova::log::log_error(s.str());
        std::abort();
    }
}

nova::shader::shader(const std::string& vertpath,const std::string& fragpath){
    std::string vertstr = openshader(vertpath);
    const char* vertsrc = vertstr.c_str();
    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glerr(glShaderSource(m_VertexShader,1,&vertsrc,nullptr));
    glerr(glCompileShader(m_VertexShader));
    compileCheck(m_VertexShader);

    std::string fragstr = openshader(fragpath);
    const char* fragsrc = fragstr.c_str();
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glerr(glShaderSource(m_FragmentShader,1,&fragsrc,nullptr));
    glerr(glCompileShader(m_FragmentShader));
    compileCheck(m_FragmentShader);
    
    glerr(m_program = glCreateProgram());
    linkshaders(m_program,m_VertexShader,m_FragmentShader);
    glerr(glLinkProgram(m_program));
    linkCheck(m_program);

    bind();
}

nova::shader::~shader(){
    this->unbind();
    glDeleteProgram(m_program);
}

void nova::shader::addUniform4f(const char* attrib,float a,float b,float c,float d){
    bind();
    glerr(auto loc = glGetUniformLocation(m_program,attrib));

    if(loc == -1){
        std::stringstream ss;
        ss << "unable to find attribute: " << attrib << '\n';
        nova::log::log_error(ss.str());
        std::abort();
    }
    glerr(glUniform4f(loc,a,b,c,d));
}

void nova::shader::addUniform1i(const char* attrib,int a){
    bind();
    glerr(auto loc = glGetUniformLocation(m_program,attrib));

    if(loc == -1){
        std::stringstream ss;
        ss << "unable to find attribute: " << attrib << '\n';
        nova::log::log_error(ss.str());
        std::abort();
    }
    glerr(glUniform1i(loc,a));
}

void nova::shader::addUniform1f(const char* attrib,float a){
    bind();
    glerr(auto loc = glGetUniformLocation(m_program,attrib));

    if(loc == -1){
        std::stringstream ss;
        ss << "unable to find attribute: " << attrib << '\n';
        nova::log::log_error(ss.str());
        std::abort();
    }
    glerr(glUniform1f(loc,a));
}

void nova::shader::addUniform2f(const char* attrib,float a,float b){
    bind();
    glerr(auto loc = glGetUniformLocation(m_program,attrib));

    if(loc == -1){
        std::stringstream ss;
        ss << "unable to find attribute: " << attrib << '\n';
        nova::log::log_error(ss.str());
        std::abort();
    }
    glerr(glUniform2f(loc,a,b));
}

void nova::shader::addUniformMat4(const char* attrib,nova::mat4& matrix)const{
    bind();
    glerr(auto loc = glGetUniformLocation(m_program,attrib));

    if(loc == -1){
        std::stringstream ss;
        ss << "Unable to find attribute: " << attrib << '\n';
        nova::log::log_error(ss.str());
        std::abort();
    }
    glerr(glUniformMatrix4fv(loc,1,true,&matrix[0][0]));
}

void nova::shader::define(const std::string& vertpath,const std::string& fragpath){
    std::string vertstr = openshader(vertpath);
    const char* vertsrc = vertstr.c_str();
    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glerr(glShaderSource(m_VertexShader,1,&vertsrc,nullptr));
    glerr(glCompileShader(m_VertexShader));
    compileCheck(m_VertexShader);

    std::string fragstr = openshader(fragpath);
    const char* fragsrc = fragstr.c_str();
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glerr(glShaderSource(m_FragmentShader,1,&fragsrc,nullptr));
    glerr(glCompileShader(m_FragmentShader));
    compileCheck(m_FragmentShader);
    
    glerr(m_program = glCreateProgram());
    linkshaders(m_program,m_VertexShader,m_FragmentShader);
    glerr(glLinkProgram(m_program));
    linkCheck(m_program);

    nova::log::log_message("Successfully created shader\n");
    bind();
}