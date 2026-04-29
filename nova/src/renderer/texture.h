#pragma once
#include"glcore.h"

namespace nova{
    class NOVA_API texture{
        int m_height, m_width, m_channels;
        bool m_flipped;
        uint m_textureId;
        int m_TextureFilter;
        int m_location;
    public:
        texture(const char* filepath,bool flipped,int texture_filter,int gltexture_location);
        //* texture filter - nearest for pixel art, linear for smooth images.
        ~texture();

        void bind();
        void unbind();

        inline int get_width(){return m_width;}
        inline int get_height(){return m_height;}
        inline int get_channels(){return m_channels;}
        inline uint get_textureId(){return m_textureId;}
        inline int get_TextureFilter(){return m_TextureFilter;}
        inline int get_TextureLocation(){return m_location;}
    };
}