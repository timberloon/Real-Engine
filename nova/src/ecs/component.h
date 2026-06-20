#pragma once
#include"ecscore.h"
namespace nova{
    #define inject\
        operator const componentID&(){return m_componentID;}\
        operator componentID&(){return m_componentID;} 

    struct NOVA_API TransformComponent{
        inline static componentID m_componentID;
        float m_points[8];
        uint m_indices[6];
        float m_width,m_height;
        nova::vec2 m_pos;

        TransformComponent(float x,float y,float w,float h){
            m_pos.a = x; m_pos.b = y;
            m_width = w; m_height = h;

            m_points[0] = x;   m_points[1] = y;
            m_points[2] = x+w; m_points[3] = y;
            m_points[4] = x+w; m_points[5] = y+h;
            m_points[6] = x;   m_points[7] = y+h;

            m_indices[0] = 0;m_indices[1] = 1;m_indices[2] = 3;
            m_indices[3] = 1;m_indices[4] = 2;m_indices[5] = 3;
        }

        inject
    };

    struct NOVA_API SpriteComponent{
        inline static componentID m_componentID;
        int m_texture_location_offset;
        const char* m_texturePath;
        bool m_flipped;
        unsigned int m_textureFilter;

        SpriteComponent(const char* path,bool flipped,unsigned int texFilter,float offset)
        : m_flipped(flipped), m_textureFilter(texFilter), m_texturePath(path), m_texture_location_offset(offset){}

        inject
    };

    struct NOVA_API ColorComponent{
        inline static componentID m_componentID;
        float r,g,b,a;
        ColorComponent(float x,float y,float z,float b) : r(x), g(y), b(z), a(b) {}

        inject
    };
}
