#include"texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include<sstream>

nova::texture::texture(const char* filepath,bool flipped,int texture_filter,int gltexture_location)
     : m_flipped(flipped), m_TextureFilter(texture_filter),m_location(gltexture_location){
        stbi_set_flip_vertically_on_load(flipped);

        unsigned char* data = nullptr;
        if(m_map.find(filepath) != m_map.end()) data = m_map[filepath];
        else {
            data = stbi_load(filepath,&m_width,&m_height,&m_channels,0);
            m_map[filepath] = data;
        }

        if(data == nullptr){
            std::stringstream s;
            s << "failed to load texture: " << filepath << '\n';
            nova::log::log_error(s.str());
            std::abort();
        }

        glerr(glActiveTexture(GL_TEXTURE0+m_location));
        glerr(glGenTextures(1,&m_textureId));
        GLenum format = (m_channels == 4) ? GL_RGBA : GL_RGB;
        glerr(glBindTexture(GL_TEXTURE_2D,m_textureId));
        glerr(glTexImage2D(GL_TEXTURE_2D,0,format,m_width,m_height,0,format,GL_UNSIGNED_BYTE,data));

        glerr(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE));
        glerr(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE));
        glerr(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,m_TextureFilter));
        glerr(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,m_TextureFilter));

        glerr(glGenerateMipmap(GL_TEXTURE_2D));
        stbi_image_free(data);

        bind();
    }

void nova::texture::bind(){
    glerr(glBindTexture(GL_TEXTURE_2D,m_textureId));
}

void nova::texture::unbind(){
    glerr(glBindTexture(GL_TEXTURE_2D,0));
}

nova::texture::~texture(){
    glerr(glDeleteTextures(1,&m_textureId));
}
